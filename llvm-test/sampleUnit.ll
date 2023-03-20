; ModuleID = 'sampleUnit'
source_filename = "sampleUnit"

@0 = private unnamed_addr constant [13 x i8] c"Hello World\0A\00", align 1
@1 = private unnamed_addr constant [17 x i8] c"Bruh moment: %d\0A\00", align 1

declare i32 @puts(ptr)

declare i32 @printf(ptr, ...)

declare i32 @fib(i32)

define i32 @main() {
entry:
  %0 = call i32 @puts(ptr @0)
  %1 = call i32 (ptr, ...) @printf(ptr @1, i32 42)
  ret i32 0
}
