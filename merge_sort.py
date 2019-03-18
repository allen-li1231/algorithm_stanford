def readFile():
    f = open(r"C:\Users\super\Desktop\IntegerArray.txt", "r")
    container = f.read().splitlines()
    f.close()

    container = [int(s) for s in container]
    return container


def sortAndCount(ary1, ary2):
    container = []
    inverse_count = 0
    for idx, i in enumerate(ary1):
        for j in ary2:
            if i <= j:
                container.append(i)
                break

            else:
                container.append(j)
                inverse_count += len(ary1) - idx
                ary2 = ary2[1:]
        if len(ary2) == 0:
            container.extend(ary1[idx:])
            break

    if len(ary2) != 0:
        container.extend(ary2)
    return container, inverse_count


def mergeAndCount(number_array, inverse_count=0):
    L = len(number_array)
    if L >= 2:
        left, left_count = mergeAndCount(number_array[:int(L / 2)], inverse_count)
        right, right_count = mergeAndCount(number_array[int(L / 2):], inverse_count)
        buffer, sort_count = sortAndCount(left, right)
        return buffer, sort_count + left_count + right_count
    else:
        return number_array, 0


if __name__ == '__main__':
    ary = readFile()
    print("Overall inverse amount is ", mergeAndCount(ary)[1])
