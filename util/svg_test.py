#!/usr/bin/python3

import svgwrite
from svgwrite import cm, mm

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

    
x = 10
y = 10
dwg = svgwrite.Drawing(filename='codes.svg', size=(210*mm, 297*mm))
addHammingCode(dwg, x, y, 13, [0, 1, 0, 1, 0, 1, 0, 1, 0])
dwg.save()


