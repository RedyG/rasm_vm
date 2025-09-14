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

void disassemble(Module module) {
    const char* instruction_names[] = {
        "nop", "br", "br_true", "br_false", "call", "call_intrinsic", "call_indirect", "call_external", "ret", "ret_void", "pop", "dup",
        "local_get", "local_set", "i8_const", "i16_const", "i32_const", "i64_const",
        "i32_eqz", "i32_eq", "i32_ne", "i32_lt", "u32_lt", "i32_gt", "u32_gt",
        "i32_le", "u32_le", "i32_ge", "u32_ge", "i64_eq", "i64_ne", "i64_lt",
        "u64_lt", "i64_gt", "u64_gt", "i64_le", "u64_le", "i64_ge", "u64_ge",
        "f32_eq", "f32_ne", "f32_lt", "f32_gt", "f32_le", "f32_ge", "f64_eq",
        "f64_ne", "f64_lt", "f64_gt", "f64_le", "f64_ge", "i32_add", "i32_sub",
        "i32_mul", "i32_div", "u32_div", "i32_rem", "u32_rem", "i32_and",
        "i32_or", "i32_xor", "i32_shl", "i32_shr", "u32_shr", "i64_add", "i64_sub",
        "i64_mul", "i64_div", "u64_div", "i64_rem", "u64_rem", "i64_and", "i64_or",
        "i64_xor", "i64_shl", "i64_shr", "u64_shr", "f32_add", "f32_sub", "f32_mul",
        "f32_div", "f64_add", "f64_sub", "f64_mul", "f64_div", "i8_load", "i16_load",
        "i32_load", "i64_load", "i8_store", "i16_store", "i32_store", "i64_store",
        "alloca", "alloca_pop", "gc_malloc", "gc_malloc_arr", "mem_cpy", "mem_cpy_s", "ptr_load_const"
    };

    Label* labels = malloc(65536 * sizeof(Label));
    uint16_t labels_count = 0;

    // Function disassembly
    for (int i = 0; i < (module.funcs_count + module.imports_count); i++) {
        Func func = module.funcs[i];
        uint8_t* ip = func.ip;


        labels_count = 0;

        printf("fn %d (args: %d, locals: %d, size: %d):\n", i, func.args_count, func.locals_count, func.size);

        // Disassemble the function
        while ((size_t)ip < (size_t)(func.ip + func.size)) {
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
            case 4:  // call
            case 5:
            case 6:
            case 7:
            {
                uint16_t func_index = *(uint16_t*)ip;
                ip += sizeof(uint16_t);
                printf(" %u", func_index);
                break;
            }
            case 12:  // local_get
            case 13: // local_set
            {
                uint16_t local_index = *(uint16_t*)ip;
                ip += sizeof(uint16_t);
                printf(" %u", local_index);
                break;
            }
            case 14:  // i8_const
            {
                int8_t value = *(int8_t*)ip;
                ip += sizeof(int8_t);
                printf(" %d", value);
                break;
            }
            case 15:  // i16_const
            {
                int16_t value = *(int16_t*)ip;
                ip += sizeof(int16_t);
                printf(" %d", value);
                break;
            }
            case 85: // i8_load
            case 86: // i16_load
            case 87: // i32_load
            case 88: // i64_load
            case 89: // i8_store
            case 90: // i16_store
            case 91: // i32_store
            case 92: // i64_store
            case 16:  // i32_const
            {
                int32_t value = *(int32_t*)ip;
                ip += sizeof(int32_t);
                printf(" %d", value);
                break;
            }
            case 17:  // i64_const
            {
                int64_t value = *(int64_t*)ip;
                ip += sizeof(int64_t);
                printf(" %lld", value);
                break;
            }
            case 93: // alloca
            case 94: // alloca_pop
            case 96: // gc_malloc_arr
            case 98: // mem_cpy_s
			case 99: // ptr_load_const
            {
                uint32_t value = *(uint32_t*)ip;
                ip += sizeof(uint32_t);
				printf(" %u", value);
				break;
            }

            case 97: // mem_cpy (i32 dest, i32 src, u32 size)
            {
                uint32_t dest = *(uint32_t*)ip;
				ip += sizeof(uint32_t);
				uint32_t src = *(uint32_t*)ip;
				ip += sizeof(uint32_t);
				uint32_t size = *(uint32_t*)ip;
				ip += sizeof(uint32_t);
				printf(" %u %u %u", dest, src, size);
				break;
            }
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
