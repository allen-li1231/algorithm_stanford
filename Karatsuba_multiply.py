"""
Author: Allen Lee
"""
'''
def speedtest(f):
    def wrapper(*args, **kwargs):
        start = time.clock()
        rt = f(*args, **kwargs)
        elapsed = time.clock() - start
        return rt, elapsed
    return wrapper
'''


def splitChar(c):
    l = len(c)
    left_figure = int(l/2)
    return c[:left_figure], c[left_figure: l+1]


def addStr(num1, num2):
    def addcarry(digit1, digit2, addon):
        # return carry and digit of the addition of two single digits and a formal carry.
        cry = (digit1 + digit2 + addon) // 10
        dig = (digit1 + digit2 + addon) % 10
        return cry, dig

    v = ''
    addon_tmp = 0
    if len(num1) < len(num2):
        tmp = num1
        num1 = num2
        num2 = tmp
    j = len(num1)-1
    k = len(num2)-1

    for i in range(j, -2, -1):
        if i < 0:       # all digits in num1 and num2 are iterated, thus can we return.
            if addon_tmp != 0:
                v = str(addon_tmp) + v
            return v
        elif k >= 0:
            c, d = addcarry(int(num1[i]), int(num2[k]), addon_tmp)
            v = str(d) + v
            addon_tmp = c
            k -= 1
        elif k < 0:
            c, d = addcarry(int(num1[i]), 0, addon_tmp)
            v = str(d) + v
            addon_tmp = c


def divStr(num1, num2):
    def divcarry(digit1, digit2, divon):
        # return carry and digit of the division of two single digits and a formal carry.
        if digit1 - digit2 >= divon:
            cry = 0
            dig = digit1 - digit2 - divon
            return cry, dig
        else:
            cry = 1
            dig = 10 - digit2 + digit1 - divon
            return cry, dig

    v = ''
    divon_tmp = 0
    j = len(num1)-1
    k = len(num2)-1
    for i in range(j, -1, -1):
        if k >= 0:
            c, d = divcarry(int(num1[i]), int(num2[k]), divon_tmp)
            v = str(d) + v
            divon_tmp = c
            k -= 1
        elif k < 0:
            c, d = divcarry(int(num1[i]), 0, divon_tmp)
            v = str(d) + v
            divon_tmp = c
    return v.lstrip('0')


def multiply(num1, num2):
    minus1 = False
    minus2 = False
    if num1[0] == '-':
        minus1 = True
        num1.lstrip('-')
    if num2[0] == '-':
        minus2 = True
        num2.lstrip('-')
    if minus1 ^ minus2:
        sign = '-'
    else:
        sign = ''

    div = 0
    nlen1 = len(num1)
    nlen2 = len(num2)
    if nlen1 < nlen2:
        div = nlen2-nlen1
        num1 = num1 + '0'*div
    elif nlen1 > nlen2:
        div = nlen1-nlen2
        num2 = num2 + '0'*div

    if len(num1) > 2:
        left1, right1 = splitChar(num1)
        left2, right2 = splitChar(num2)
        right_lenth = len(right1)
        bd = multiply(right1, right2)
        ac = multiply(left1, left2)
        a_add_b_mul_c_add_d = multiply(addStr(left1, right1), addStr(left2, right2))
        ad_add_bc = divStr(divStr(a_add_b_mul_c_add_d, ac), bd)
        answer = addStr(ac + '0'*2*right_lenth, bd)
        answer = addStr(answer, ad_add_bc + '0'*right_lenth)

        if div != 0:
            return sign + answer[:-div]
        else:
            return sign + answer
    else:
        return sign + str(int(num1) * int(num2))


if __name__ == '__main__':
    num1 = input("Please insert first number: ")
    num2 = input("Please insert second number: ")
    print(multiply(num1, num2))
