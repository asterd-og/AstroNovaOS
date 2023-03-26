extern intHandler

%macro intStub 1
intStub%+%1:
    push 0
    push %1
    pusha
    call intHandler
    popa
    iret
%endmacro

%assign i 0
%rep 256
    intStub i
    %assign i i+1
%endrep

global intVector
intVector:
    %assign j 0
    %rep 256
        dd intStub%+j
        %assign j j+1
    %endrep