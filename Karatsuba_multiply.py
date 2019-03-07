"""
Author: Allen Lee
"""


def splitChar(c):
    l = len(c)
    left_figure = int(l/2)
    return c[:left_figure], c[left_figure: l+1]


def addInStr(num1, num2):
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


def minusInStr(num1, num2):
    def minuscarry(digit1, digit2, mison):
        # return carry and digit of the subtraction of two single digits and a formal carry.
        if digit1 - digit2 >= mison:
            cry = 0
            dig = digit1 - digit2 - mison
            return cry, dig
        else:
            cry = 1
            dig = 10 - digit2 + digit1 - mison
            return cry, dig

    v = ''
    mison_tmp = 0
    j = len(num1)-1
    k = len(num2)-1
    for i in range(j, -1, -1):
        if k >= 0:
            c, d = minuscarry(int(num1[i]), int(num2[k]), mison_tmp)
            v = str(d) + v
            mison_tmp = c
            k -= 1
        elif k < 0:
            c, d = minuscarry(int(num1[i]), 0, mison_tmp)
            v = str(d) + v
            mison_tmp = c
    return v.lstrip('0')


def multiply(num1, num2):
    if num1 == '0' or num2 == '0':
        return '0'
    # determining whether the answer will be positive or negative.
    minus1 = False
    minus2 = False
    if num1[0] == '-':
        minus1 = True
        num1 = num1.lstrip('-')
    if num2[0] == '-':
        minus2 = True
        num2 = num2.lstrip('-')
    if minus1 ^ minus2:
        sign = '-'
    else:
        sign = ''
    # make the two numbers the same in digits.
    nlen1 = len(num1)
    nlen2 = len(num2)
    if nlen1 < nlen2:
        num1 = '0'*(nlen2-nlen1) + num1
    elif nlen1 > nlen2:
        num2 = '0'*(nlen1-nlen2) + num2

    if len(num1) > 9:
        left1, right1 = splitChar(num1)
        left2, right2 = splitChar(num2)
        right_lenth = len(right1)
        # applying Karatsuba formula...
        bd = multiply(right1, right2)
        ac = multiply(left1, left2)
        a_add_b_mul_c_add_d = multiply(addInStr(left1, right1), addInStr(left2, right2))
        ad_add_bc = minusInStr(minusInStr(a_add_b_mul_c_add_d, ac), bd)
        answer = addInStr(ac + '0'*2*right_lenth, bd)
        answer = addInStr(answer, ad_add_bc + '0'*right_lenth)

        return sign + answer.lstrip('0')
    else:
        # numbers length less than 9 don't have to iterate.
        return sign + str(int(num1) * int(num2))


if __name__ == '__main__':
    num1 = input("Please insert first number: ")
    num2 = input("Please insert second number: ")
    print(multiply(num1, num2))
