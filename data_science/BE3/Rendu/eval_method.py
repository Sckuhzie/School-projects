from sklearn.metrics import (
    accuracy_score,
    precision_score,
    recall_score,
    confusion_matrix,
    cohen_kappa_score,
    f1_score,
    roc_auc_score,
)
from sklearn.preprocessing import label_binarize
import numpy as np


def eval_method(y_test, y_pred):
    res = {}
    accuracy = accuracy_score(y_test, y_pred)
    print("Accuracy : ", accuracy)
    res["accuracy"] = accuracy

    y_true = label_binarize(y_test, classes=np.unique(y_test))
    y_score = label_binarize(y_pred, classes=np.unique(y_test))
    roc_auc = roc_auc_score(y_true, y_score, average="macro", multi_class="ovr")
    print("ROC AUC Score : ", roc_auc)
    res["roc_auc"] = roc_auc

    if len(set(y_test)) == 2:
        precision = precision_score(y_test, y_pred)
        print("Precision : ", precision)
        res["precision"] = precision
        recall = recall_score(y_test, y_pred)
        print("Recall : ", recall)
        res["recall"] = recall
        f1 = f1_score(y_test, y_pred)
        print("F1 Score : ", f1)
        res["f1-score"] = f1

    kappa = cohen_kappa_score(y_test, y_pred)
    print("Kappa : ", kappa)
    res["kappa"] = kappa
    confusion = confusion_matrix(y_test, y_pred)
    print("Confusion Matrix :\n", confusion)
    res["confusion"] = confusion
    return res
