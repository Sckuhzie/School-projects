import torch
from torch.utils import data
import numpy as np

from torchvision import transforms
import os
from PIL import Image
import matplotlib.pyplot as plt

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")


def load_data(folder, split=0.8, batch_size=32):
    class CustomDataset(data.Dataset):
        def __init__(self, image_folder, mask_folder, transform=None):
            self.image_folder = image_folder
            self.mask_folder = mask_folder
            self.transform = transform
            self.image_files = sorted(os.listdir(image_folder))
            self.mask_files = sorted(os.listdir(mask_folder))

        def __len__(self):
            return len(self.image_files)

        def __getitem__(self, idx):
            image_path = os.path.join(self.image_folder, self.image_files[idx])
            mask_path = os.path.join(self.mask_folder, self.mask_files[idx])
            image = Image.open(image_path).convert("RGB")
            mask = Image.open(mask_path).convert("L")

            if self.transform:
                image = self.transform(image)
                mask = self.transform(mask)

            return image, mask

    transform = transforms.Compose(
        [transforms.Resize((128, 128)), transforms.ToTensor()]
    )

    image_folder = os.path.join(folder, "images")
    mask_folder = os.path.join(folder, "masks")

    dataset = CustomDataset(image_folder, mask_folder, transform=transform)
    train_size = int(split * len(dataset))
    validation_size = len(dataset) - train_size
    train_dataset, validation_dataset = data.random_split(
        dataset, [train_size, validation_size]
    )

    train_loader = data.DataLoader(train_dataset, batch_size=32, shuffle=True)
    validation_loader = data.DataLoader(
        validation_dataset, batch_size=32, shuffle=False
    )

    return train_loader, validation_loader


def train_model(model, n_epoch, train_loader, validation_loader, file_output, learning_rate=0.001):
    model.train()
    train_loss_list = []
    validation_loss_list = []
    best_validation_loss = np.inf
    early_stopping = 0
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
    criterion = torch.nn.BCELoss()

    for epoch in range(n_epoch):

        if early_stopping > 10:
            break

        train_loss = 0.0
        for batch in train_loader:
            x, y = batch
            x, y = x.to(device), y.to(device)
            y_pred = model(x)
            loss = criterion(y_pred, y)
            train_loss += loss.detach().cpu().item() / len(train_loader)

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

        train_loss_list.append(train_loss)
        print(f"Epoch: {epoch}\nTraining loss: {train_loss:.2f}")

        model.eval()
        with torch.no_grad():
            valid_loss = 0.0
            for batch in validation_loader:
                x, y = batch
                x, y = x.to(device), y.to(device)
                y_pred = model(x)
                loss = criterion(y_pred, y)
                valid_loss += loss.detach().cpu().item() / len(validation_loader)

        validation_loss_list.append(valid_loss)
        print(f"Validation Loss: {valid_loss:.2f}\n")

       
        if valid_loss < best_validation_loss:
            best_validation_loss = valid_loss
            torch.save(model.state_dict(), file_output)
            early_stopping = 0
        else:
            early_stopping += 1
        if early_stopping == 5:
            learning_rate = 0.1*learning_rate
            optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
            print(f"Learning rate reduced to {learning_rate}\n")
            

    return train_loss_list, validation_loss_list
