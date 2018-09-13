#!/usr/bin/python3

# Create hamming codes for 5 bit values encoded in 9 bits
# for values in the range 0 to 20.
#
# This according to the method described here:
# http://users.cis.fiu.edu/~downeyt/cop3402/hamming.html

import svgwrite
from svgwrite import cm, mm

BORDER_SIZE = 2
ZERO_SIZE = BORDER_SIZE
ONE_SIZE = ZERO_SIZE*2

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
    inA = list(reversed([int(x) for x in list(fmt.format(n))]))
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
    # Add a label with the number which is encoded, and the direction markers
    bitmarks = dwg.add(dwg.g(id='bitmarks'))
    bitmarks.add(dwg.text('%d' % value, ((xmm-BORDER_SIZE)*mm, ymm*mm)))
    
    # draw arrow to show direction of travel
    bitmarks.add(dwg.line(start=((xmm+5)*mm,(ymm-1)*mm), end=((xmm+5-1.5)*mm, (ymm+1)*mm), stroke='black'))
    bitmarks.add(dwg.line(start=((xmm+5)*mm,(ymm-1)*mm), end=((xmm+5+1.5)*mm, (ymm+1)*mm), stroke='black'))
    bitmarks.add(dwg.line(start=((xmm+5+1.5)*mm, (ymm+1)*mm), end=((xmm+5-1.5)*mm, (ymm+1)*mm), stroke='black'))

    ymm += BORDER_SIZE

    # put a black rectangle under the bit marks
    rect_y = ((len(bits)+1)*BORDER_SIZE) + (len(bits)*ONE_SIZE)
    bitmarks.add(dwg.rect(insert=((xmm-BORDER_SIZE)*mm, ymm*mm), size=((10+(2*BORDER_SIZE))*mm, (rect_y*mm)), fill='black'))

    ymm += BORDER_SIZE

    for i in range(0, len(bits)):
        # Put a label on the left side for helping with debugging
        bitmarks.add(dwg.text(str(bits[i]), ((xmm-4)*mm, (ymm+1.5+bits[i])*mm)))
        # add a white bar with height dependant on bit on/off
        ysize = ZERO_SIZE if bits[i] is 0 else ONE_SIZE
        bitmarks.add(dwg.rect(insert=(xmm*mm, (ymm)*mm), size=(10*mm, ysize*mm), fill='white'))
        ymm += ysize
        bitmarks.add(dwg.rect(insert=(xmm*mm, (ymm)*mm), size=(10*mm, BORDER_SIZE*mm), fill='black'))
        ymm += BORDER_SIZE

    
# Make codes for our desired range of inputs
marks_per_row = 8
dwg = svgwrite.Drawing(filename='codes.svg', size=(210*mm, 297*mm), style="font-size:2mm; font-family:Arial")

n=0
for i in range(1,25):
    xg = n % marks_per_row
    yg = int(n/marks_per_row)
    x = 30 + (xg*20)
    y = 20 + (yg*85)
    addHammingCode(dwg, x, y, i, ham(i, 8, 12))
    n+=1

dwg.save()


