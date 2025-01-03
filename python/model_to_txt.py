"""
Converts the state dict of our (Pytorch) Model Class
into a txt file. All weights are dumped as they are.
"""

import numpy as np
import torch

from utils import GIT_ROOT

MODEL_PATH = f"{GIT_ROOT}/models/model.pth"
CPP_MODEL_DIR = f"{GIT_ROOT}/cpp/model/"

class Translator:
    """
    Translates pth file to txt file (weights only)
    """
    def __init__(self, model: object) -> None:
        self.model = model
        self.keys = {key[:9].split(".")[-1] for key in model.keys()}

    def __getitem__(self, idx: int) -> torch.Tensor:
        """Gets the Tensor weights of a given layer"""
        ws = self.model[f"network.{idx}.weight"].cpu().numpy()
        bias = self.model[f"network.{idx}.bias"].cpu().numpy()
        new_ws = np.concatenate((ws.transpose(), [bias])).transpose()
        return new_ws

    def save(self, path):
        """
        Saves all the layers' weights into txt file
        """
        keys = list(self.keys)
        keys.sort()
        for i, key in enumerate(keys):
            data = self[key]
            np.savetxt(f"{path}/{i}.txt", data, comments='')


def main() -> None:
    """
    Main script
    """
    model = torch.load(MODEL_PATH)
    translator = Translator(model)
    translator.save(CPP_MODEL_DIR)

if __name__ == '__main__':
    main()
