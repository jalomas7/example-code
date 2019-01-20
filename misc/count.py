import sys

def count():

    counter = {}

    for line in sys.stdin:
        for word in line.split():
            item = counter.get(word, 0)
            counter[word] = item + 1


    for word, total in sorted(counter.items(), key=lambda elem : elem[0]):
        print(word, ':', total)


if __name__ == '__main__':
    count()
