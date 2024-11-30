import numpy as np
import torch

from utils import GIT_ROOT

model_path = f"{GIT_ROOT}/models/model.pth"
cpp_model_dir = f"{GIT_ROOT}/cpp/model/"

class Translator:
    def __init__(self, model: object):
        self.model = model
        self.keys = set([key[:9].split(".")[-1] for key in model.keys()])

    def __getitem__(self, idx: int) -> torch.Tensor:
        ws = self.model[f"network.{idx}.weight"].cpu().numpy()
        bias = self.model[f"network.{idx}.bias"].cpu().numpy()
        new_ws = np.concatenate((ws.transpose(), [bias])).transpose()
        return new_ws

    def save(self, path):
        keys = list(self.keys)
        keys.sort()
        for i, key in enumerate(keys):
            np.savetxt(f"{path}/{i}.txt", self.__getitem__(key))


def main():
    model = torch.load(model_path)
    translator = Translator(model)
    translator.save(cpp_model_dir)

if __name__ == '__main__':
    main()
