class heap:
    def __init__(self, data=None, rule='+'):
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

    def _readFile(self, file_path: str):
        with open(file_path, 'r') as f:
            temp = f.readlines()

        container = [int(num.strip('\n')) for num in temp]
        return container

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

    def _rootRearrange(self):
        if self.len == 2:
            if self._compareRule(self.values[1], self.values[0]):
                temp = self.values[0]
                self.values[0] = self.values[1]
                self.values[1] = temp
            return
        elif self.len < 2:
            return

        idx = 0
        left_child_idx = 1
        right_child_idx = 2
        number = self.values[0]

        while right_child_idx < self.len and (  # determine whether new root violate heap rule
                self._compareRule(self.values[left_child_idx], number) or
                self._compareRule(self.values[right_child_idx], number)
        ):
            # determine which child to swap
            if self._compareRule(self.values[left_child_idx], self.values[right_child_idx]):
                self.values[idx] = self.values[left_child_idx]
                self.values[left_child_idx] = number
                idx = left_child_idx
                right_child_idx = (idx + 1) * 2
                left_child_idx = right_child_idx - 1

            else:
                self.values[idx] = self.values[right_child_idx]
                self.values[right_child_idx] = number
                idx = right_child_idx
                left_child_idx = idx * 2 + 1
                right_child_idx = left_child_idx + 1

        if left_child_idx == self.len - 1 and self._compareRule(self.values[left_child_idx], number):
            self.values[idx] = self.values[left_child_idx]
            self.values[left_child_idx] = number

    def setHeap(self, iterable):
        self.values = []
        for number in iterable:
            self.insert(number)

    def insert(self, number: int):
        self.values.append(number)
        self._bubbleUp(self.len - 1)

    def extremeExtract(self, show_extract=True):
        if self.len == 0:
            raise Exception("Nothing to extract.")
        if show_extract:
            if self.rule == '+':
                print("extract min: %d" % self.values[0])
            else:
                print("extract max: %d" % self.values[0])

        self.values[0] = self.values[-1]
        self.values.pop()
        self._rootRearrange()

    def delete(self, index):
        print("delete number: %d" % self.values[index])
        if self.rule == '+':
            self.values[index] = float("-inf")
        else:
            self.values[index] = float("inf")

        self._bubbleUp(index)
        self.extremeExtract(show_extract=False)

    def initHomework(self, file_path: str):
        self.setHeap(self._readFile(file_path))


inc = heap([5, 3, 2, 6, 7, 6, 4], '-')
