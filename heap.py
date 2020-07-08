"""
@Author: Allen Lee      2019/4/18
"""


class heap:
    def __init__(self, data: list, rule='+'):
        if rule not in ['+', '-']:
            raise ValueError("Wrong heap rule, use '+' denotes increment heap and '-' denotes decrement heap.")

        self.rule = rule
        self.values = []
        self.setHeap(data)

    @property
    def len(self):
        return len(self.values)

    @property
    def height(self):
        if self.len == 0:
            return 0
        h = 0
        while self.len >= 2 ** h:
            h += 1
        return h

    def _compareRule(self, a, b):
        if self.rule == '+':
            return a < b
        elif self.rule == '-':
            return a > b

    def _bubbleUp(self, index):
        parent_idx = int((index - 1) / 2)
        number = self.values[index]
        while parent_idx >= 0 and self._compareRule(number, self.values[parent_idx]):
            self.values[index] = self.values[parent_idx]
            self.values[parent_idx] = number
            index = parent_idx
            parent_idx = int((parent_idx - 1) / 2)
        # print(self.values)

    def _bubbleDown(self, index):
        right_child_idx = (index + 1) * 2
        left_child_idx = right_child_idx - 1
        number = self.values[index]

        while right_child_idx < self.len and (  # determine whether new root violate heap rule
                self._compareRule(self.values[left_child_idx], number) or
                self._compareRule(self.values[right_child_idx], number)
        ):
            # determine which child to swap
            if self._compareRule(self.values[left_child_idx], self.values[right_child_idx]):
                self.values[index] = self.values[left_child_idx]
                self.values[left_child_idx] = number
                index = left_child_idx
                right_child_idx = (index + 1) * 2
                left_child_idx = right_child_idx - 1

            else:
                self.values[index] = self.values[right_child_idx]
                self.values[right_child_idx] = number
                index = right_child_idx
                left_child_idx = index * 2 + 1
                right_child_idx = left_child_idx + 1

        if left_child_idx == self.len - 1 and self._compareRule(self.values[left_child_idx], number):
            self.values[index] = self.values[left_child_idx]
            self.values[left_child_idx] = number

    def _rootRearrange(self):
        if self.len == 2:
            if self._compareRule(self.values[1], self.values[0]):
                temp = self.values[0]
                self.values[0] = self.values[1]
                self.values[1] = temp
            return
        elif self.len < 2:
            return

        self._bubbleDown(0)

    def setHeap(self, iterable):
        self.values = []
        for number in iterable:
            self.insert(number)

    def insert(self, number: int):
        self.values.append(number)
        self._bubbleUp(self.len - 1)

    def extremeExtract(self, show_extract=False):
        if self.len == 0:
            raise Exception("Nothing to extract.")
        pop_value = self.values[0]
        if show_extract:
            if self.rule == '+':
                print("extract min: %d" % pop_value)
            else:
                print("extract max: %d" % pop_value)

        self.values[0] = self.values[-1]
        self.values.pop()
        self._rootRearrange()
        return pop_value

    def delete(self, index: int):
        print("delete number: %d" % self.values[index])
        if self.rule == '+':
            self.values[index] = float("-inf")
        else:
            self.values[index] = float("inf")

        self._bubbleUp(index)
        self.extremeExtract(show_extract=False)


def readFile(file_path: str):
    with open(file_path, 'r') as f:
        temp = f.readlines()

    container = [int(num.strip('\n')) for num in temp]
    return container


def _mediumRebalanced(num, max_h: heap, min_h: heap):
    vmax = max_h.values[0]
    if num <= vmax:
        max_h.insert(num)
    else:
        min_h.insert(num)

    l1 = max_h.len - min_h.len
    if l1 > 1:
        vmax = max_h.extremeExtract()
        min_h.insert(vmax)
    elif l1 < -1:
        vmin = min_h.extremeExtract()
        max_h.insert(vmin)
    elif l1 == -1:
        return min_h.values[0]

    return max_h.values[0]


def mediumExtractor(data: list):
    if len(data) == 0:
        raise Exception("Nothing to extract.")
    elif len(data) == 1:
        return data

    container = [data[0]]
    if data[0] >= data[1]:
        container.append(data[1])
        min_h = heap([data[0]], rule='+')
        max_h = heap([data[1]], rule='-')
    else:
        container.append(data[0])
        min_h = heap([data[1]], rule='+')
        max_h = heap([data[0]], rule='-')

    for i in range(2, len(data)):
        v = _mediumRebalanced(data[i], max_h, min_h)
        container.append(v)

    return container


def main():
    data = readFile(r"./data/Median.txt")
    ans = mediumExtractor(data)
    print("Homework answer: %d" % (sum(ans) % 10000))


if __name__ == "__main__":
    main()
