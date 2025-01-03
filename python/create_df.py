"""
Creates a csv from pandas dataframe which links
every image to its right class.
"""
import os
import glob
import pandas as pd

from utils import GIT_ROOT


def main() -> None:
    """
    Main function of the script.
    """
    imgs_path = sorted(glob.glob(f"{GIT_ROOT}/data/pgm/*.pgm"))
    data = {
        "image_name": [os.path.basename(fpath) for fpath in imgs_path],
        "Stenosis": [int("Positive" in fpath) for fpath in imgs_path] 
    }
    df = pd.DataFrame(data).set_index("image_name")
    df.to_csv(f"{GIT_ROOT}/data/stenosis_608.csv")


if __name__ == '__main__':
    main()
