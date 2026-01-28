import torch
import torch.nn as nn
import torch.nn.functional as F

input_dimensions = (128, 128, 3)

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

class UNET_no_pooling(nn.Module):

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.conv1 = nn.Conv2d(3, 16, 3, padding=1)
        self.conv1_2 = nn.Conv2d(16, 16, 3, padding=1)
        self.down1 = nn.Conv2d(16, 16, 3, stride=2, padding=1)

        self.conv2 = nn.Conv2d(16, 32, 3, padding=1)
        self.conv2_2 = nn.Conv2d(32, 32, 3, padding=1)
        self.down2 = nn.Conv2d(32, 32, 3, stride=2, padding=1)

        self.conv3 = nn.Conv2d(32, 64, 3, padding=1)
        self.conv3_2 = nn.Conv2d(64, 64, 3, padding=1)
        self.down3 = nn.Conv2d(64, 64, 3, stride=2, padding=1)

        self.conv4 = nn.Conv2d(64, 128, 3, padding=1)
        self.conv4_2 = nn.Conv2d(128, 128, 3, padding=1)
        self.down4 = nn.Conv2d(128, 128, 3, stride=2, padding=1)

        self.conv5 = nn.Conv2d(128, 256, 3, padding=1)
        self.conv5_2 = nn.Conv2d(256, 256, 3, padding=1)

        self.up6 = nn.ConvTranspose2d(256, 128, 2, stride=2)
        self.conv6 = nn.Conv2d(256, 128, 3, padding=1)
        self.conv6_2 = nn.Conv2d(128, 128, 3, padding=1)

        self.up7 = nn.ConvTranspose2d(128, 64, 2, stride=2)
        self.conv7 = nn.Conv2d(128, 64, 3, padding=1)
        self.conv7_2 = nn.Conv2d(64, 64, 3, padding=1)

        self.up8 = nn.ConvTranspose2d(64, 32, 2, stride=2)
        self.conv8 = nn.Conv2d(64, 32, 3, padding=1)
        self.conv8_2 = nn.Conv2d(32, 32, 3, padding=1)

        self.up9 = nn.ConvTranspose2d(32, 16, 2, stride=2)
        self.conv9 = nn.Conv2d(32, 16, 3, padding=1)
        self.conv9_2 = nn.Conv2d(16, 16, 3, padding=1)

        self.conv10 = nn.Conv2d(16, 1, 1)

    def forward(self, x):
        c1 = F.relu(self.conv1(x))
        c1 = F.relu(self.conv1_2(c1))
        p1 = self.down1(c1)

        c2 = F.relu(self.conv2(p1))
        c2 = F.relu(self.conv2_2(c2))
        p2 = self.down2(c2)

        c3 = F.relu(self.conv3(p2))
        c3 = F.relu(self.conv3_2(c3))
        p3 = self.down3(c3)

        c4 = F.relu(self.conv4(p3))
        c4 = F.relu(self.conv4_2(c4))
        p4 = self.down4(c4)

        c5 = F.relu(self.conv5(p4))
        c5 = F.relu(self.conv5_2(c5))

        u6 = self.up6(c5)
        u6 = torch.cat([u6, c4], dim=1)
        c6 = F.relu(self.conv6(u6))
        c6 = F.relu(self.conv6_2(c6))

        u7 = self.up7(c6)
        u7 = torch.cat([u7, c3], dim=1)
        c7 = F.relu(self.conv7(u7))
        c7 = F.relu(self.conv7_2(c7))

        u8 = self.up8(c7)
        u8 = torch.cat([u8, c2], dim=1)
        c8 = F.relu(self.conv8(u8))
        c8 = F.relu(self.conv8_2(c8))

        u9 = self.up9(c8)
        u9 = torch.cat([u9, c1], dim=1)
        c9 = F.relu(self.conv9(u9))
        c9 = F.relu(self.conv9_2(c9))

        c10 = self.conv10(c9)
        output = torch.sigmoid(c10)
        return output
