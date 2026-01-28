from read_cifar import read_cifar, split_data
from mlp import run_mlp_training
import matplotlib.pyplot as plt

if __name__ == "__main__":
    data, labels = read_cifar("data")

    train_data, train_labels, test_data, test_labels = split_data(data, labels, 0.9)

    train_accuracies, test_accuracie = run_mlp_training(
        data_train=train_data,
        labels_train=train_labels,
        data_test=test_data,
        labels_test=test_labels,
        d_h=64,
        learning_rate=0.1,
        num_epoch=100,
    )

    print(test_accuracie)

    plt.plot(train_accuracies, label="train")
    plt.xlabel("Epoch")
    plt.ylabel("Accuracy")
    plt.title("Evolution of the accuracy according to the number of epochs")
    plt.savefig("results/mlp.png")

    plt.show()
