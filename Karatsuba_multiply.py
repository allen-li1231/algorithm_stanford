def splitChar(c):
    l = len(c)
    left_figure = int(l/2)
    return c[:left_figure], c[left_figure: l+1]


def addStr(num1, num2):
    def carry(digit1, digit2, addon):       # return the carry and digit of two single digits and a carry of formal add.
        cry = (digit1 + digit2 + addon) // 10
        dig = (digit1 + digit2 + addon) % 10
        return cry, dig

    v = ''
    addon_tmp = 0
    l = len(num1)
    for i in range(l-1, -2, -1):
        if i == l-1:
            c, d = carry(int(num1[i]), int(num2[i]), 0)
            v += str(d)
            addon_tmp = c
        elif i == -1:       # i = -1 indicates all digits in num1 and num2 are iterated, thus can we return.
            if addon_tmp != 0:
                v = str(addon_tmp) + v
            return v
        else:
            c, d = carry(int(num1[i]), int(num2[i]), addon_tmp)
            v = str(d) + v
            addon_tmp = c



def multiply(num1, num2):
    if len(num1) > 9:
        left1, right1 = splitChar(num1)
        left2, right2 = splitChar(num2)
        a = int(left1)
        b = int(right1)
        c = int(left2)
        d = int(right2)

        bd = multiply(right1, right2)
        ac = multiply(left1, left1)
        ad_add_bc = multiply(str(a+b), str(c+d))
        return multiply(left1, right1), multiply(left2, right2)
    else:
        pass