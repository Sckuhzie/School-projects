import numpy as np


def learn_once_mse(
    w1: np.ndarray,
    b1: np.ndarray,
    w2: np.ndarray,
    b2: np.ndarray,
    data: np.ndarray,
    targets: np.ndarray,
    learning_rate: float,
):
    # forward pass
    a0 = data
    z1 = np.matmul(a0, w1) + b1
    a1 = 1 / (1 + np.exp(-z1))
    z2 = np.matmul(a1, w2) + b2
    a2 = 1 / (1 + np.exp(-z2))
    predictions = a2

    loss = np.mean(np.square(predictions - targets))

    # Backward pass
    dCda2 = 2 * (a2 - targets) / targets.shape[0]
    dCdz2 = dCda2 * a2 * (1 - a2)
    dCdw2 = np.matmul(a1.T, dCdz2)
    dCdb2 = np.sum(dCdz2, axis=0, keepdims=True)
    dCda1 = np.matmul(dCdz2, w2.T)
    dCdz1 = dCda1 * a1 * (1 - a1)
    dCdw1 = np.matmul(a0.T, dCdz1)
    dCdb1 = np.sum(dCdz1, axis=0, keepdims=True)

    w1 = w1 - learning_rate * dCdw1
    b1 = b1 - learning_rate * dCdb1
    w2 = w2 - learning_rate * dCdw2
    b2 = b2 - learning_rate * dCdb2

    return w1, b1, w2, b2, loss


def one_hot(labels: np.ndarray):
    n = labels.shape[0]
    res = np.zeros((n, max(labels) + 1))
    for i in range(n):
        res[i][labels[i]] = 1
    return res


def softmax(x):
    e_x = np.exp(x - np.max(x, axis=1, keepdims=True))
    return e_x / e_x.sum(axis=1, keepdims=True)


def learn_once_cross_entropy(
    w1: np.ndarray,
    b1: np.ndarray,
    w2: np.ndarray,
    b2: np.ndarray,
    data: np.ndarray,
    targets: np.ndarray,
    learning_rate: float,
):
    # forward pass
    a0 = data
    z1 = np.matmul(a0, w1) + b1
    a1 = 1 / (1 + np.exp(-z1))
    z2 = np.matmul(a1, w2) + b2
    a2 = softmax(z2)
    predictions = a2

    # Cross entropy loss
    y = one_hot(targets)
    loss = -np.mean(np.sum(y * np.log(predictions + 1e-9), axis=1))
    # 1e-9 is added to avoid log(0)

    # Backward pass
    dCdz2 = a2 - y
    dCdw2 = np.matmul(a1.T, dCdz2)
    dCdb2 = np.sum(dCdz2, axis=0, keepdims=True)
    dCda1 = np.matmul(dCdz2, w2.T)
    dCdz1 = dCda1 * a1 * (1 - a1)
    dCdw1 = np.matmul(a0.T, dCdz1)
    dCdb1 = np.sum(dCdz1, axis=0, keepdims=True)

    w1 = w1 - learning_rate * dCdw1
    b1 = b1 - learning_rate * dCdb1
    w2 = w2 - learning_rate * dCdw2
    b2 = b2 - learning_rate * dCdb2

    return w1, b1, w2, b2, loss


def train_mlp(
    w1: np.ndarray,
    b1: np.ndarray,
    w2: np.ndarray,
    b2: np.ndarray,
    data_train: np.ndarray,
    labels_train: np.ndarray,
    learning_rate: float,
    num_epoch: int,
):
    train_accuracies = np.zeros((num_epoch), dtype=np.float32)
    for i in range(num_epoch):
        print(f"Epoch {i}")
        w1, b1, w2, b2, loss = learn_once_cross_entropy(
            w1=w1,
            b1=b1,
            w2=w2,
            b2=b2,
            data=data_train,
            targets=labels_train,
            learning_rate=learning_rate,
        )
        train_accuracies[i] = test_mlp(w1, b1, w2, b2, data_train, labels_train)
        print(f"        Loss: {loss}")
    return w1, b1, w2, b2, train_accuracies


def test_mlp(
    w1: np.ndarray,
    b1: np.ndarray,
    w2: np.ndarray,
    b2: np.ndarray,
    data_test: np.ndarray,
    labels_test: np.ndarray,
):
    a0 = data_test
    z1 = np.matmul(a0, w1) + b1
    a1 = 1 / (1 + np.exp(-z1))
    z2 = np.matmul(a1, w2) + b2
    a2 = softmax(z2)
    predictions = a2

    test_accuracy = labels_test.flatten() == np.argmax(predictions, axis=1)

    return np.mean(test_accuracy)


def run_mlp_training(
    data_train: np.ndarray,
    labels_train: np.ndarray,
    data_test: np.ndarray,
    labels_test: np.ndarray,
    d_h: int,
    learning_rate: float,
    num_epoch: int,
):
    d_in = data_train.shape[1]
    d_out = one_hot(labels_train).shape[1]

    w1 = 2 * np.random.rand(d_in, d_h) - 1
    b1 = np.zeros((1, d_h))
    w2 = 2 * np.random.rand(d_h, d_out) - 1
    b2 = np.zeros((1, d_out))

    w1, b1, w2, b2, train_accuracies = train_mlp(
        w1=w1,
        b1=b1,
        w2=w2,
        b2=b2,
        data_train=data_train,
        labels_train=labels_train,
        learning_rate=learning_rate,
        num_epoch=num_epoch,
    )

    test_accuracies = test_mlp(
        w1=w1,
        b1=b1,
        w2=w2,
        b2=b2,
        data_test=data_test,
        labels_test=labels_test,
    )

    return train_accuracies, test_accuracies


if __name__ == "__main__":
    from read_cifar import split_data, read_cifar_batch

    # from time import time

    data, labels = read_cifar_batch("data/data_batch_1")

    train_data, train_labels, test_data, test_labels = split_data(data, labels, 0.1)
    # train_labels = one_hot(train_labels)
    # test_labels = one_hot(test_labels)

    train_accuracies, test_accuracy = run_mlp_training(
        data_train=train_data,
        labels_train=train_labels,
        data_test=test_data,
        labels_test=test_labels,
        d_h=64,
        learning_rate=0.5,
        num_epoch=30,
    )

    print(test_accuracy)
    print(train_accuracies)

    import matplotlib.pyplot as plt

    plt.plot(train_accuracies, label="train")
    # plt.plot(test_accuracies, label="test")
    # plt.ylim([-0.1, 1.1])
    plt.legend()
    plt.show()
