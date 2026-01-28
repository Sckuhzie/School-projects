import gymnasium as gym
import torch
import torch.nn as nn
import torch.nn.functional as F

import gymnasium as gym


class Agent(nn.Module):
    def __init__(self):
        super(Agent, self).__init__()
        self.fc1 = nn.Linear(4, 128)
        self.dropout = nn.Dropout(p=0.6)
        self.fc2 = nn.Linear(128, 2)

    def forward(self, x):
        x = F.relu(self.fc1(x))
        x = self.dropout(x)
        return F.softmax(self.fc2(x), dim=-1)


# Create the environment
env = gym.make("CartPole-v1")

# Reset the environment and get the initial observation


agent = Agent()
agent.load_state_dict(torch.load("reinforce_cartpole.pth"))
agent.eval()

nb_success = 0

for i in range(100):
    if i % 10 == 0:
        print(i)
    terminated = False
    nb_iter = 0
    observation = env.reset()[0]
    while not terminated and nb_iter < 500:

        probabilities = agent(torch.tensor(observation).float())
        action = torch.multinomial(probabilities, 1).item()
        # Apply the action to the environment
        # Returns next observation, reward, done signal (indicating
        # if the episode has ended), and an additional info dictionary
        observation, reward, terminated, truncated, info = env.step(action)
        # Render the environment to visualize the agent's behavior
        # env.render()
        nb_iter += 1

    if nb_iter >= 500:
        nb_success += 1

env.close()

print(f"Number of successful episodes: {nb_success}/100")
