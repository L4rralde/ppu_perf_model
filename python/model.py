"""
Multi-Layer Perceptron for Stenosis images classification
"""
import torch
from torch import nn
from torch.utils.data import DataLoader, random_split

from utils import GIT_ROOT
from dataset import Stenosis608DataSet, ToTensor

DEVICE = (
    "mps" if torch.backends.mps.is_available()
    else "cpu"
)


print(f"Using {DEVICE} DEVICE")

class Perceptron(nn.Module):
    """
    Model archite3cture classs
    """
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
        """Model's prediction"""
        x = self.flatten(x)
        return self.network(x)

    def __str__(self) -> str:
        return "Perceptron()"

def train(dataloader, model, loss_fn, optimizer):
    """
    Trains the model given a dataloader, a loss function
    and an optimizer.
    """
    model.train()
    for _, (x, y) in enumerate(dataloader):
        x = x.to(DEVICE)
        y = y.to(DEVICE)
        pred = model(x)
        loss = loss_fn(pred, y)

        loss.backward()
        optimizer.step()
        optimizer.zero_grad()

        #if batch % 10 == 0:
        #    loss = loss.item()
        #    current = (batch + 1)*len(x)
        #    print(f"loss: {loss} [{current:}/{size}]")

def test(dataloader, model, loss_fn):
    """
    Assest trained model on validation/test data
    given a loss function.
    """
    size = len(dataloader.dataset)
    num_batches = len(dataloader)
    model.eval()
    test_loss = 0
    correct = 0
    with torch.no_grad():
        for x, y in dataloader:
            x = x.to(DEVICE)
            y = y.to(DEVICE)
            pred = model(x)
            test_loss += loss_fn(pred, y).item()
            correct += (pred.argmax(1) == y).type(torch.float).sum().item()
    test_loss /= num_batches
    correct /= size
    print("Test Error")
    print(f"Accuracy: {(100*correct)}, Avg loss: {test_loss}")
    return correct, test_loss


def initialize_weights(m):
    """Initialize the wights of a non-trained model"""
    if isinstance(m, nn.Linear):
        nn.init.xavier_uniform_(m.weight)
        nn.init.zeros_(m.bias)


def main():
    """
    Main script
    """
    model = Perceptron().to(DEVICE)
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
        accuracy, test_loss = test(test_dataloader, model, loss_fn)

        # Early stopping based on test loss
        if accuracy > 0.85 and test_loss < 2.0:
            model_path = f"{GIT_ROOT}/models/{accuracy}_{test_loss}.pth"
            print("Saving model")
            torch.save(model.state_dict(), model_path)
        if test_loss > 5.0:
            break

    print("Done!")

if __name__ == '__main__':
    main()
