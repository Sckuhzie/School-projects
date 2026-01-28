import matplotlib.pyplot as plt
import torchvision.transforms as transforms
import torch
import os

from PIL import Image

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# model = UNET().to(device)
# model.load_state_dict(torch.load("unet_v1.pth", map_location=device))
# model.eval()

image = "competition_data/train/images/0b73b427d1.png"
mask = "competition_data/train/masks/0b73b427d1.png"




def test_on_image(image, model, threshold=0.5):
    image_path = os.path.join("competition_data/train/images", image)
    mask_path = os.path.join("competition_data/train/masks", image)
    input_image = Image.open(image_path).convert("RGB")
    preprocess = transforms.Compose(
        [
            transforms.Resize((128, 128)),
            transforms.ToTensor(),
            # transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
        ]
    )
    input_tensor = preprocess(input_image).unsqueeze(0).to(device)

    with torch.no_grad():
        output = model(input_tensor)

    output_image = output.squeeze().cpu().numpy()
    predicted_mask = 1.0 * (output_image > threshold)

    fig, axs = plt.subplots(1, 4, figsize=(20, 5))

    # Original image
    axs[0].imshow(input_image)
    axs[0].set_title("Original Image")
    axs[0].axis("off")

    # Real mask
    real_mask = Image.open(mask_path).convert("L")
    axs[1].imshow(real_mask, cmap="gray")
    axs[1].set_title("Real Mask")
    axs[1].axis("off")

    # Model output
    axs[2].imshow(output_image, cmap="gray")
    axs[2].set_title("Model Output")
    axs[2].axis("off")

    # Predicted mask
    axs[3].imshow(predicted_mask, cmap="gray")
    axs[3].set_title("Predicted Mask")
    axs[3].axis("off")


    plt.show()


def score_model(model, image, threshold=0.5):
    image_path = os.path.join("competition_data/train/images", image)
    mask_path = os.path.join("competition_data/train/masks", image)
    input_image = Image.open(image_path).convert("RGB")
    preprocess = transforms.Compose(
        [
            transforms.Resize((128, 128)),
            transforms.ToTensor(),
            # transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
        ]
    )
    input_tensor = preprocess(input_image).unsqueeze(0).to(device)

    with torch.no_grad():
        output = model(input_tensor)

    output_image = output.squeeze().cpu().numpy()
    predicted_mask = 1.0 * (output_image > threshold)
    mask_image = Image.open(mask_path).convert("L")

    mask_tensor = preprocess(mask_image).unsqueeze(0).to(device)

    precision = (
        torch.sum(predicted_mask * mask_tensor).item()
        / torch.sum(predicted_mask).item()
    )
    recall = (
        torch.sum(predicted_mask * mask_tensor).item() / torch.sum(mask_tensor).item()
    )

    return precision, recall


def test_threshold(model, threshold):
    precisions = []
    recalls = []
    for image in os.listdir("competition_data/train/images"):
        precision, recall = score_model(model, image, threshold)
        precisions.append(precision)
        recalls.append(recall)

    return precisions, recalls