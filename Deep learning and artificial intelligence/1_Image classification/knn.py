import numpy as np


def distance_matrix(data_test: np.ndarray, data_train: np.ndarray) -> np.ndarray:

    sx = np.sum(data_test**2, axis=1, keepdims=True)
    sy = np.sum(data_train**2, axis=1, keepdims=True)

    return np.sqrt(-2 * data_test.dot(data_train.T) + sx + sy.T)


def knn_predict(dists: np.ndarray, labels_train: np.ndarray, k: int) -> np.ndarray:
    num_test = dists.shape[0]
    y_pred = np.zeros(num_test, dtype=labels_train.dtype)

    for i in range(num_test):
        closest_y = []
        sorted_indices = np.argsort(dists[i])
        closest_y = labels_train[sorted_indices[:k]]

        y_pred[i] = np.bincount(closest_y).argmax()

    return y_pred


def evaluate_knn(
    data_train: np.ndarray,
    labels_train: np.ndarray,
    data_test: np.ndarray,
    labels_test: np.ndarray,
    k: int,
) -> float:
    dists = distance_matrix(data_test, data_train)

    print("Predicting")
    y_pred = knn_predict(dists, labels_train, k)

    good_predict = np.sum(y_pred == labels_test)
    print(f"Good predictions: {good_predict}")
    print(f"Total predictions: {labels_test.shape[0]}")
    return good_predict / labels_test.shape[0]


if __name__ == "__main__":
    from read_cifar import read_cifar, split_data
    from time import time

    tic = time()

    data, labels = read_cifar("data")
    train_data, train_labels, test_data, test_labels = split_data(data, labels, 0.9)
    accuracy = evaluate_knn(train_data, train_labels, test_data, test_labels, 10)
    print(accuracy)

    print("temps : ", time() - tic)
