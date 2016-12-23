#!/usr/bin/python3

# Create hamming codes for 5 bit values encoded in 9 bits
# for values in the range 0 to 20.
#
# This according to the method described here:
# http://users.cis.fiu.edu/~downeyt/cop3402/hamming.html

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

# Make codes for our desired range of inputs
for i in range(0,21):
    print(i, ham(i, 5, 9))

