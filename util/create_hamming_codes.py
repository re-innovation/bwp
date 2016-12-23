#!/usr/bin/python3

# Create hamming codes for 5 bit values encoded in 9 bits
# for values in the range 0 to 20.
#
# This according to the method described here:
# http://users.cis.fiu.edu/~downeyt/cop3402/hamming.html

import svgwrite
from svgwrite import cm, mm

def parityAddress(n, bits=12):
    '''Get which bits go to make partity for specified bit

    Arguments:
    n -- the address of the bit of output
    bits -- the length of the output

    Returns:
    a list of bit addresses in the output which are used to 
    generate the partity bit at address n. If n is a data bit
    (i.e. not used to store parity), return None
    '''

    if n+1 in [2**x for x in range(0,5)]:
        a = []
        check = True
        left = n+1
        for i in range(n, bits):
            if left == 0:
                left = n+1
                check = not check
            if check:
                a.append(i)
            left -= 1
        return a[1:]
    else:
        return None

def ham(n, dataBits, outputBits):
    '''Create hamming code from unhammed data

    Arguments:
    n -- the value of the data to be hammed
    dataBits -- how many bits to front 0-pad input to when 
                converted to binary
    outputBits -- length of hamming code output in bits

    Returns:
    hamming code for data n in outputBits bits length
    '''
    # convert integer to list of bit values
    fmt = "{:0%sb}" % dataBits
    inA = [int(x) for x in list(fmt.format(n))]
    outA = []

    # fill in data into non-parity slots
    idx = 0
    parityBits = []
    for i in range(0, outputBits):
        pa = parityAddress(i, outputBits)
        if pa is None:
            outA.append(inA[idx])
            idx += 1
        else:
            outA.append(None)
            parityBits.append(i)

    for i in parityBits:
        pa = parityAddress(i, outputBits)
        outA[i] = sum(outA[x] for x in pa) % 2

    return outA

def addHammingCode(dwg, xmm, ymm, value, bits):
    dwg.add(dwg.text(str(value), (xmm*mm, ymm*mm)))
    bitmarks = dwg.add(dwg.g(id='bitmarks'))
    ymm += 2
    on = True

    # put a black rectangle under the bit marks
    bitmarks.add(dwg.rect(insert=((xmm-2)*mm, ymm*mm), size=(14*mm, ((5*9)*mm)), fill='black'))
    ymm += 2
    for i in range(0, len(bits)):
        ysize = 4 if bits[i] else 2
        bitmarks.add(dwg.rect(insert=(xmm*mm, (ymm+2)*mm), size=(10*mm, ysize*mm), fill='white' if on else 'black'))
        on = not on
        ymm += ysize

    
# Make codes for our desired range of inputs
marks_per_row = 8
dwg = svgwrite.Drawing(filename='codes.svg', size=(210*mm, 297*mm))
for i in range(0,23):
    xg = i % marks_per_row
    yg = int(i/marks_per_row)
    x = 30 + (xg*20)
    y = 30 + (yg*60)
    # print(i, ham(i, 5, 9))
    addHammingCode(dwg, x, y, i, ham(i, 5, 9))

dwg.save()


