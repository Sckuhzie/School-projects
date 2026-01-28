from read_cifar import read_cifar, split_data
from knn import evaluate_knn
import matplotlib.pyplot as plt

if __name__ == "__main__":

    data, labels = read_cifar("data")
    train_data, train_labels, test_data, test_labels = split_data(data, labels, 0.9)
    accuracy_list = []

    for k in range(1, 21):
        accuracy_list.append(
            evaluate_knn(train_data, train_labels, test_data, test_labels, k)
        )
        print(k)

    plt.figure,
    plt.plot(range(1, 21), accuracy_list)
    plt.xlabel("k")
    plt.ylabel("Accuracy")
    plt.title("Accuracy of knn method")
    plt.savefig("results/knn.png")
