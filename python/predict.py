"""
Uses MLP to predict the label of the first image of
the Stenosis600 Data set.
"""

import torch

from utils import GIT_ROOT
from model import Perceptron
from dataset import Stenosis608DataSet, ToTensor

PATH = f"{GIT_ROOT}/models/model.pth"

def main() -> None:
    """Main function of the script"""
    model = Perceptron()
    model.load_state_dict(torch.load(PATH, weights_only=True))
    stenosis_dataset = Stenosis608DataSet(
        f"{GIT_ROOT}/data/stenosis_608.csv",
        f"{GIT_ROOT}/data/pgm/",
        ToTensor()
    )
    x, _ = stenosis_dataset[0]
    print(model(x).detach().numpy())

if __name__ == '__main__':
    main()
