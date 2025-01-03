"""
Interfaces the StenosisDataset to Pytorch's DataSet object
"""
import os

import torch
import pandas as pd
import numpy as np
from torch.utils.data import Dataset

from utils import read_pgm

class Stenosis608DataSet(Dataset):
    """
    StenosisDataset in Pytorch format
    """
    def __init__(self, annotation_file: str, img_dir: str, transform: object = None):
        self.img_label = pd.read_csv(annotation_file)
        self.img_dir = img_dir
        self.transform = transform

    def __len__(self) -> int:
        return len(self.img_label)

    def __getitem__(self, idx) -> tuple:
        if torch.is_tensor(idx):
            idx = idx.tolist()
        img_path = os.path.join(
            self.img_dir, self.img_label.iloc[idx, 0]
        )
        if not os.path.exists(img_path):
            raise FileNotFoundError(f"Image file not found: {img_path}")
        image = read_pgm(img_path).astype('float32') / 127.5 - 1.0
        label = int(self.img_label.iloc[idx, 1])
        if self.transform:
            image = self.transform(image)
        return (image, label)

class ToTensor():
    """
    Built-in transform for torch.vision
    """
    def __call__(self, image: np.ndarray) -> torch.Tensor:
        image = torch.from_numpy(image).unsqueeze(0)  # Shape: (1, H, W)
        return image

    def __repr__(self) -> str:
        return "Built-in ToTensor()"
