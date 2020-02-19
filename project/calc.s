            AREA |.text|, CODE, READONLY
            
calc        PROC
            EXPORT calc         ; export so that cpp file can read from it
            CMP R2, #1          ; when #1 then add -- R2 being the selection from C file
            BEQ add
            CMP R2, #2          ; when #2 then subtract
            BEQ subtract  
            CMP R2, #3          ; when #3 then multiply
            BEQ multiply
            CMP R2, #4          ; when #4 then divide
            BEQ division        ; if equals to above then go to that code
            B stop              ; branch stop
            
add         ADD R0, R1          ; R0 being the first value from the C program, and R1 being the second
            BX LR               ; return from branch function
            B stop
            
subtract    SUB R0, R1
            BX LR
            B stop

multiply    MUL R0, R1
            BX LR
            B stop
            
division    UDIV R0, R1         ; unsigned division because we didn't program a way for initial number to be negative 
            BX LR
            B stop      
            
stop       
            ENDP
            ALIGN
            END