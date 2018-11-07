import math

import matplotlib.pyplot as plt
import numpy as np
import pandas


def sigmoid(x):
    return 1 / (1 + np.exp(-x))


def propagate(w, b, X, Y):
    """
    Returns the cost and gradient for X, Y with weights beta

    Arguments:
    w -- weights, shape (num_feat, 1)
    b -- bias, a scalar
    X -- data of shape (num_feat, m)
    Y -- labels of size (1, m)
    """

    # Number of examples
    m = X.shape[1]

    # Forward propagation
    A = sigmoid(np.dot(w.T, X) + b)
    

    # Cost
    EPS = 0.0000000001
    cost = -1 / m * np.sum(Y * np.log(A + EPS) + (1 - Y) * np.log(1 - A + EPS))
    cost = np.squeeze(cost)

    # Backward propragation
    dw = 1 / m * np.dot(X, (A - Y).T)
    db = 1 / m * np.sum(A - Y)

    grads = {"dw": dw,
             "db": db}

    return grads, cost


def train(w, b, X, Y, num_iterations, lr, print_every):
    """
    Arguments:
    w -- weights, shape (num_feat, 1)
    b -- bias, a scalar
    Y -- labels of size (1, m)
    """

    costs = []
    for i in range(num_iterations):
        grads, cost = propagate(w, b, X, Y)

        dw = grads["dw"]
        db = grads["db"]

        w -= lr * dw
        b -= lr * db


        # Record the costs
        if i % print_every == 0:
            costs.append(cost)

        if print_every > 0 and i % print_every == 0:
            lr *= 0.99
            pred_train = predict(w, b, X)
            print("Cost after iteration %i: %f, lr: %s, accuracy: %s" % (i, cost, lr, (100 - np.mean(np.abs(pred_train - Y)) * 100)))

    params = {"w": w, "b": b}
    grads = {"dw": dw, "db": db}

    return params, grads, costs


def predict(w, b, X):
    """
    Arguments:
    w -- weights, shape (num_feat, 1)
    b -- bias, a scalar
    X -- data of shape (num_feat, m)
    """

    m = X.shape[1]
    pred = np.zeros((1, m))
    w = w.reshape(X.shape[0], 1)

    A = sigmoid(np.dot(w.T, X) + b)

    for i in range(A.shape[1]):
        pred[0, i] = 1 if A[0, i] > 0.5 else 0

    return pred


def init_params(num_feat):
    w = np.zeros([num_feat, 1])
    b = 0
    return w, b


def model(X_train, Y_train, X_test, num_iterations=2000, lr=0.5, print_every=0):
    w, b = init_params(X_train.shape[0])

    params, grads, costs = train(w, b, X_train, Y_train, num_iterations, lr, print_every)
    
    w = params["w"]
    b = params["b"]

    pred_test = predict(w, b, X_test)
    pred_train = predict(w, b, X_train)

    print("train accuracy: {} %".format(100 - np.mean(np.abs(pred_train - Y_train)) * 100))

    
    d = {"costs": costs,
         "Y_prediction_test": pred_test, 
         "Y_prediction_train" : pred_train, 
         "w" : w, 
         "b" : b,
         "learning_rate" : lr,
         "num_iterations": num_iterations}
    
    return d


def preprocess(dataset, is_train=True):
    sex = [1 if i == 'male' else 0 for i in dataset['Sex']]
    pclass = dataset['Pclass']
    age = [0 if math.isnan(i) else i for i in dataset['Age']]
    SibSp = dataset['SibSp']
    Parch = dataset['Parch']
    Fare = dataset['Fare']
    X = np.concatenate(([sex], [pclass], [age], [SibSp], [Parch], [Fare]))

    if is_train:
        survived = dataset['Survived']
        Y = np.array([survived])
        return X, Y
    else:
        return X


def main():
    train_dataset = pandas.read_csv('data/train.csv')
    test_dataset = pandas.read_csv('data/test.csv')

    X_train, Y_train = preprocess(train_dataset)
    X_test = preprocess(test_dataset, is_train=False)

    d = model(X_train, Y_train, X_test,
            num_iterations = 200000,
            lr = 0.01,
            print_every = 5000)


if __name__ == "__main__":
    main()
