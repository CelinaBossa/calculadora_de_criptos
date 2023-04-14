#; Multiply two 64-bit floating-point numbers (a and b) and store the result in result
#; Inputs: xmm0 = a, xmm1 = b
#; Outputs: xmm0 = result

.section .text
    .global multiply

multiply:
    mulsd %xmm1, %xmm0  #; Multiply a by b, result in xmm0
    ret                 #; Return
