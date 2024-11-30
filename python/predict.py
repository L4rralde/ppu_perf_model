import torch
import numpy as np

from utils import GIT_ROOT
from model import Perceptron
from dataset import Stenosis608DataSet, ToTensor

PATH = f"{GIT_ROOT}/models/model.pth"

def main():
    model = Perceptron()
    model.load_state_dict(torch.load(PATH, weights_only=True))
    stenosis_dataset = Stenosis608DataSet(
        f"{GIT_ROOT}/data/stenosis_608.csv",
        f"{GIT_ROOT}/data/pgm/",
        ToTensor()
    )
    X, y = stenosis_dataset[0]
    print(model(X).detach().numpy())

if __name__ == '__main__':
    main()
