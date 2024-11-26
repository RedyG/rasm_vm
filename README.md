# RedyLang VM
A bytecode interpreter written in C. Target output of https://github.com/RedyG/RedyLangCompiler

## Main implemented features
* stack machine bytecode
* module/import system
* basic arithmetic
* local variables
* memory allocation on stack and heap ( malloc and alloca )

## Current instruction set
|   | 0         | 1         | 2         | 3         | 4     | 5       | 6       | 7         | 8       | 9           | A           | B | C         | D         | E         | F         |
|---|-----------|-----------|-----------|-----------|-------|---------|---------|-----------|---------|-------------|-------------|---|-----------|-----------|-----------|-----------|
| 0 | `nop`     | `br`      | `br_true` | `br_false`| `exit`| `call`  | `ret`   | `ret_void`| `pop`   | `local_get` | `local_set` |   | `i8_const`| `i16_const`| `i32_const`| `i64_const`|
| 1 | `i32_eqz` | `i32_eq`  | `i32_ne`  | `i32_lt`  | `u32_lt`| `i32_gt`| `u32_gt`| `i32_le`  | `u32_le`| `i32_ge`   | `u32_ge`   |   | `i64_eq`  | `i64_ne`  | `i64_lt`  | `u64_lt`  |
| 2 | `i64_gt`  | `u64_gt`  | `i64_le`  | `u64_le`  | `i64_ge`| `u64_ge`| `f32_eq`| `f32_ne`  | `f32_lt`| `f32_gt`   | `f32_le`   | `f32_ge` | `f64_eq` | `f64_ne` | `f64_lt` | `f64_gt` |
| 3 | `f64_le`  | `f64_ge`  | `i32_add` | `i32_sub` | `i32_mul`| `i32_div`| `u32_div`| `i32_rem`| `u32_rem`| `i32_and` | `i32_or`   | `i32_xor`| `i32_shl`| `i32_shr`| `u32_shr`| `i64_add`|
| 4 | `i64_sub` | `i64_mul` | `i64_div` | `u64_div` | `i64_rem`| `u64_rem`| `i64_and`| `i64_or`| `i64_xor`| `i64_shl` | `i64_shr` | `u64_shr`| `f32_add`| `f32_sub`| `f32_mul`| `f32_div`|
| 5 | `f64_add` | `f64_sub` | `f64_mul` | `f64_div` | `i8_load`| `i16_load`| `i32_load`| `i64_load`| `i8_store`| `i16_store`| `i32_store`| `i64_store`| `alloca` | `alloca_pop` | `gc_malloc` | `mem_cpy` |
| 6 | `mem_cpy_s`|           |           |           |       |         |         |           |         |             |             |   |           |           |           |           |

## Exemple ( fibonacci of 10 )

```asm
fn 0 (args: 0, locals: 0): // main
  i8_const 10
  call 1
  exit

fn 1 (args: 1, locals: 0): // fib
  local_get 0
  i8_const 2
  i32_lt
  br_false 0
_:
  local_get 0
  ret
0:
  local_get 0
  i8_const 1
  i32_sub
  call 1
  local_get 0
  i8_const 2
  i32_sub
  call 1
  i32_add
  ret
```

## What's next?
* GC support
* Multithreading
* full IEEE 754 float support
* SIMD instructions
