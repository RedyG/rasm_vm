#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Func.h"

typedef struct Label {
    uint8_t* pos;
    uint16_t num;
} Label;

Label* find_label(Label* labels, uint16_t labels_count, uint8_t* pos) {
    for (int i = 0; i < labels_count; i++) {
		if (labels[i].pos == pos) {
			return &labels[i];
		}
	}
    return NULL;
}

void disassemble(uint8_t* program) {
    // Ignore magic number and version
    program += 16;

    // Read the number of functions
    uint16_t funcs_count = *(uint16_t*)program;
    program += sizeof(uint16_t);

    // Read function table
    ProtocolFunc* protocol_funcs = (ProtocolFunc*)program;
    program += funcs_count * sizeof(ProtocolFunc);

    const char* instruction_names[] = {
        "nop", "br", "br_true", "br_false", "exit", "", "call", "ret", "pop",
        "local_get", "local_set", "", "i8_const", "i16_const", "i32_const", "i64_const",
        "i32_eqz", "i32_eq", "i32_ne", "i32_lt", "u32_lt", "i32_gt", "u32_gt",
        "i32_le", "u32_le", "i32_ge", "u32_ge", "", "i64_eq", "i64_ne", "i64_lt",
        "u64_lt", "i64_gt", "u64_gt", "i64_le", "u64_le", "i64_ge", "u64_ge",
        "f32_eq", "f32_ne", "f32_lt", "f32_gt", "f32_le", "f32_ge", "f64_eq",
        "f64_ne", "f64_lt", "f64_gt", "f64_le", "f64_ge", "i32_add", "i32_sub",
        "i32_mul", "i32_div", "u32_div", "i32_rem", "u32_rem", "i32_and",
        "i32_or", "i32_xor", "i32_shl", "i32_shr", "u32_shr", "i64_add", "i64_sub",
        "i64_mul", "i64_div", "u64_div", "i64_rem", "u64_rem", "i64_and", "i64_or",
        "i64_xor", "i64_shl", "i64_shr", "u64_shr", "f32_add", "f32_sub", "f32_mul",
        "f32_div", "f64_add", "f64_sub", "f64_mul", "f64_div"
    };

    Label* labels = malloc(65536 * sizeof(Label));
    uint16_t labels_count = 0;

    // Function disassembly
    for (int i = 0; i < funcs_count; i++) {
        printf("fn %d (args: %d, locals: %d):\n", i, protocol_funcs[i].args_count, protocol_funcs[i].locals_count);

        // Jump to the function's code section
        uint8_t* ip = program + protocol_funcs[i].offset;

        // Calculate the function end by checking the next function's offset (or end of code section for the last function)
        uint32_t function_end = (i + 1 < funcs_count) ? protocol_funcs[i + 1].offset : 0xFFFFFFFF;

        labels_count = 0;

        // Disassemble the function
        while ((ip - program) < function_end) {
            Label* label = find_label(labels, labels_count, ip);
            if (label != NULL)
                printf("%u:\n", label->num);

            uint8_t opcode = *ip++;
            const char* instr_name = instruction_names[opcode];

            if (*instr_name == '\0') {
                printf("Unknown instruction: %u\n", opcode);
                break;
            }

            printf("  %s", instr_name);

            switch (opcode) {
            case 1:  // br
            case 2:  // br_true
            case 3:  // br_false
            {
                int16_t offset = *(int16_t*)ip;
                ip += sizeof(int16_t);

                uint8_t* pos = ip + offset;
                Label* label = find_label(labels, labels_count, pos);
                if (label == NULL) {
                    labels[labels_count] = (Label){ ip + offset, labels_count };

                    printf(" %u", labels_count);

                    labels_count++;
                } else {
                    printf(" %u", label->num);
                }

                if (opcode == 2 || opcode == 3)
					printf("\n_:");
                break;
            }
            case 6:  // call
            {
                uint16_t func_index = *(uint16_t*)ip;
                ip += sizeof(uint16_t);
                printf(" %u", func_index);
                break;
            }
            case 9:  // local_get
            case 10: // local_set
            {
                uint16_t local_index = *(uint16_t*)ip;
                ip += sizeof(uint16_t);
                printf(" %u", local_index);
                break;
            }
            case 12:  // i8_const
            {
                int8_t value = *(int8_t*)ip;
                ip += sizeof(int8_t);
                printf(" %d", value);
                break;
            }
            case 13:  // i16_const
            {
                int16_t value = *(int16_t*)ip;
                ip += sizeof(int16_t);
                printf(" %d", value);
                break;
            }
            case 14:  // i32_const
            {
                int32_t value = *(int32_t*)ip;
                ip += sizeof(int32_t);
                printf(" %d", value);
                break;
            }
            case 15:  // i64_const
            {
                int64_t value = *(int64_t*)ip;
                ip += sizeof(int64_t);
                printf(" %lld", value);
                break;
            }
            case 5:  // exit
                printf("\n");
                goto end_function;  // End function disassembly
            default:
                break;
            }

            printf("\n");
        }
    end_function:
        printf("\n");
    }

    free(labels);
}
