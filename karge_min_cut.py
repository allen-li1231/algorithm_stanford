"""
@Author: Allen Lee      2019/3
"""
import random

import numpy as np
import pandas as pd


class kargeMinCut():
    def __init__(self, seed=None):
        self.set = None
        self.seed = seed

    def readFile(self, file_path):
        with open(file_path, 'r') as f:
            container = f.readlines()
        container = [x.strip('\n').split('\t')[:-1] for x in container]

        self.set = pd.DataFrame(container, dtype=np.int64)
        self.set.set_index(0, inplace=True)

        # for undefined reason, the integer data type should be reassigned in order not to cause bugs.
        def intify(row):
            for i, num in enumerate(row.values):
                if num:
                    row.iloc[i] = np.int64(num)
                else:
                    row.iloc[i] = np.nan
            return row

        self.set = self.set.apply(intify, axis=1)

    def _fuse(self, graph_set):
        """
        Step1: randomly pick two vertices v1 and v2 from the set;
        Step2: fuse relations between v2 and other vertices into v1;
        Step3: truncate v2;
        Step4: replace v2 relation in other vertices with v1;
        :return: a graph set that has iterated once.
        """
        if self.seed:
            self.seed += 1
            random.seed(self.seed)

        v1 = random.choice(graph_set.index)
        v1_row = graph_set.loc[v1].dropna()
        v2 = random.choice(v1_row.values[v1_row.values != v1])

        container = []
        for num in graph_set.loc[v2]:
            if pd.notnull(num):
                num = int(num)
                if num != v1:
                    container.append(num)

        temp = v1_row.append(pd.Series(container), ignore_index=True)
        temp.drop(temp.index[temp.values == v2], inplace=True)
        temp = pd.DataFrame(temp.values, index=range(1, len(temp) + 1), columns=[v1, ]).T
        graph_set.drop(v1, inplace=True)
        graph_set.drop(v2, inplace=True)
        graph_set = pd.concat([temp, graph_set], axis=0)
        graph_set.replace(v2, v1, inplace=True)
        return graph_set

    def recurse_and_count(self):
        s = self.set.copy()
        while s.shape[0] != 2:
            s = self._fuse(s)
        return s


if __name__ == "__main__":
    ins = kargeMinCut()
    ins.readFile(file_path=r"C:\Users\super\Desktop\kargerMinCut.txt")

    container = []
    for i in range(20):
        print("Iteration:", i + 1)
        a = ins.recurse_and_count()
        v1 = sum(pd.notnull(a.iloc[0]))
        container.append(v1)

    print("Possible min cut:", min(container))
