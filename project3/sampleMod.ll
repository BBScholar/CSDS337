; ModuleID = 'sampleMod'
source_filename = "sampleMod"

define i32 @simple() {
entry:
  ret i32 0
}

define i32 @add(i32 %0, i32 %1) {
entry:
  %2 = add i32 %0, %1
  ret i32 %2
}

define float @addIntFloat(i32 %0, float %1) {
entry:
  %2 = sitofp i32 %0 to float
  %3 = fadd float %2, %1
  ret float %3
}

define i32 @conditional(i1 %0) {
entry:
  %1 = alloca i32, align 4
  br i1 %0, label %if_true, label %if_false

if_true:                                          ; preds = %entry
  store i32 3, ptr %1, align 4
  br label %after

if_false:                                         ; preds = %entry
  store i32 5, ptr %1, align 4
  br label %after

after:                                            ; preds = %if_false, %if_true
  %2 = load i32, ptr %1, align 4
  %3 = add i32 %2, 11
  ret i32 %3
}

define i32 @oneTwoPhi(i1 %0) {
entry:
  br i1 %0, label %if_true, label %if_false

if_true:                                          ; preds = %entry
  br label %after

if_false:                                         ; preds = %entry
  br label %after

after:                                            ; preds = %if_false, %if_true
  %1 = phi i32 [ 3, %if_true ], [ 5, %if_false ]
  %2 = add i32 %1, 11
  ret i32 %2
}

define i32 @selection(i1 %0) {
entry:
  %1 = select i1 %0, i32 3, i32 5
  %2 = add i32 %1, 11
  ret i32 %2
}

declare ptr @malloc(i32)

declare void @free(ptr)

define void @heapTest() {
entry:
  %0 = call ptr @malloc(i32 32)
  store i32 32, ptr %0, align 4
  call void @free(ptr %0)
  ret void
}
