import pickle
import numpy as np
import os


def read_cifar_batch(file: str) -> tuple[np.ndarray, np.ndarray]:
    with open(file, "rb") as fo:
        dict = pickle.load(fo, encoding="bytes")
    data = np.array(dict[b"data"], dtype=np.float32)
    labels = np.array(dict[b"labels"], dtype=np.int64)
    return data, labels


def read_cifar(directory: str) -> tuple[np.ndarray, np.ndarray]:

    data = np.empty((0, 3072), dtype=np.float32)
    labels = np.empty(0, dtype=np.int64)

    for batch in range(1, 6):
        batch_file = os.path.join(directory, f"data_batch_{batch}")
        temp_data, temp_labels = read_cifar_batch(batch_file)
        data = np.concatenate((data, temp_data), axis=0)
        labels = np.concatenate((labels, temp_labels), axis=0)

    batch_file = os.path.join(directory, "test_batch")
    temp_data, temp_labels = read_cifar_batch(batch_file)
    data = np.concatenate((data, temp_data), axis=0)
    labels = np.concatenate((labels, temp_labels), axis=0)

    return data, labels


def split_data(
    data: np.ndarray, labels: np.ndarray, split: float
) -> tuple[np.ndarray, np.ndarray, np.ndarray, np.ndarray]:
    n = data.shape[0]
    indices = np.random.permutation(n)
    split = int(n * split)
    training_idx, test_idx = indices[:split], indices[split:]
    return data[training_idx], labels[training_idx], data[test_idx], labels[test_idx]


if __name__ == "__main__":
    data, labels = read_cifar_batch("data/data_batch_1")
    print(data.shape)
    print(labels.shape)

    data, labels = read_cifar("data")
    print(data.shape)
    print(labels.shape)

    train_data, train_labels, test_data, test_labels = split_data(data, labels, 0.8)
    print(train_data.shape)
    print(train_labels.shape)
    print(test_data.shape)
    print(test_labels.shape)
