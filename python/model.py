
import torch
from torch import nn
from torch.utils.data import DataLoader, random_split

from utils import GIT_ROOT
from dataset import Stenosis608DataSet, ToTensor

device = (
    "mps" if torch.backends.mps.is_available()
    else "cpu"
)


print(f"Using {device} device")

class Perceptron(nn.Module):
    def __init__(self):
        super().__init__()
        self.flatten = nn.Flatten()
        self.network = nn.Sequential(
            nn.Linear(64*64, 1024),  # First hidden layer
            nn.ReLU(),
            nn.Linear(1024, 256),    # Second hidden layer
            nn.ReLU(),
            nn.Linear(256, 64),      # Third hidden layer
            nn.ReLU(),
            nn.Linear(64, 2)         # Output layer
        )
       

    def forward(self, x):
        x = self.flatten(x)
        return self.network(x)

def train(dataloader, model, loss_fn, optimizer):
    size = len(dataloader.dataset)
    model.train()
    for batch, (X, y) in enumerate(dataloader):
        X = X.to(device)
        y = y.to(device)
        pred = model(X)
        loss = loss_fn(pred, y)

        loss.backward()
        optimizer.step()
        optimizer.zero_grad()

        #if batch % 10 == 0:
        #    loss = loss.item()
        #    current = (batch + 1)*len(X)
        #    print(f"loss: {loss} [{current:}/{size}]")

def test(dataloader, model, loss_fn):
    size = len(dataloader.dataset)
    num_batches = len(dataloader)
    model.eval()
    test_loss = 0
    correct = 0
    with torch.no_grad():
        for X, y in dataloader:
            X = X.to(device)
            y = y.to(device)
            pred = model(X)
            test_loss += loss_fn(pred, y).item()
            correct += (pred.argmax(1) == y).type(torch.float).sum().item()
    test_loss /= num_batches
    correct /= size
    print("Test Error")
    print(f"Accuracy: {(100*correct)}, Avg loss: {test_loss}")


def initialize_weights(m):
    if isinstance(m, nn.Linear):
        nn.init.xavier_uniform_(m.weight)
        nn.init.zeros_(m.bias)


def main():
    model = Perceptron().to(device)
    model.apply(initialize_weights)
    loss_fn = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=1e-3)

    stenosis_dataset = Stenosis608DataSet(
        f"{GIT_ROOT}/data/stenosis_608.csv",
        f"{GIT_ROOT}/data/pgm/",
        ToTensor()
    )

    # Split dataset
    train_size = int(0.8 * len(stenosis_dataset))
    test_size = len(stenosis_dataset) - train_size
    train_dataset, test_dataset = random_split(
        stenosis_dataset,
        [train_size, test_size]
    )

    train_dataloader = DataLoader(train_dataset, batch_size=8, shuffle=True)
    test_dataloader = DataLoader(test_dataset, batch_size=8)

    epochs = 100
    for t in range(epochs):
        print(f"Epoch {t+1}")
        train(train_dataloader, model, loss_fn, optimizer)
        test(test_dataloader, model, loss_fn)
    print("Done!")

if __name__ == '__main__':
    main()
