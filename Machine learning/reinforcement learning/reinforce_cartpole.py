import gymnasium as gym
import torch
import torch.nn as nn
import torch.nn.functional as F
import matplotlib.pyplot as plt
import numpy as np
from torch.distributions import Categorical
from collections import deque

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
# Create the environment
env = gym.make("CartPole-v1")  # , render_mode="human")

# Reset the environment and get the initial observation
observation = env.reset()


# Creation of the agent
class Policy(nn.Module):
    def __init__(self):
        super(Policy, self).__init__()
        self.fc1 = nn.Linear(4, 128)
        self.dropout = nn.Dropout()
        self.fc2 = nn.Linear(128, 2)

    def forward(self, x):
        x = F.relu(self.fc1(x))
        x = self.dropout(x)
        return F.softmax(self.fc2(x), dim=1)

    def act(self, state):
        """
        Given a state, take action
        """
        state = torch.from_numpy(state).float().unsqueeze(0).to(device)
        probs = self.forward(state).cpu()
        m = Categorical(probs)
        action = m.sample()
        return action.item(), m.log_prob(action)


gamma = 0.99
policy = Policy()
policy.train()
loss_list = []
reward_list = []
optimizer = torch.optim.Adam(policy.parameters(), lr=5e-3)
max_t = 500

# Train
for k in range(500):
    if k % 10 == 0:
        print(k)
    observation = env.reset()[0]

    # Reset buffers
    log_prob_buffer = []
    reward_buffer = []

    terminated = False
    while not terminated and len(reward_buffer) < max_t:
        # for k in range(10):

        action, probabilities = policy.act(observation)

        log_prob_buffer.append(probabilities)

        observation, reward, terminated, truncated, info = env.step(action)
        reward_buffer.append(reward)

    # print(proba_buffer)
    # print(action_buffer)
    # print(reward_buffer)

    reward_list.append(sum(reward_buffer))

    returns = deque(maxlen=max_t)
    for t in range(len(reward_buffer))[::-1]:
        disc_return_t = returns[0] if len(returns) > 0 else 0
        returns.appendleft(gamma * disc_return_t + reward_buffer[t])

    eps = np.finfo(np.float32).eps.item()
    returns = torch.tensor(returns)
    returns = (returns - returns.mean()) / (returns.std() + eps)

    loss = []
    for log_prob, disc_return in zip(log_prob_buffer, returns):
        loss.append(-log_prob * disc_return)
    loss = torch.cat(loss).sum()

    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    loss_list.append(loss.item())

torch.save(policy.state_dict(), "reinforce_cartpole.pth")

plt.plot(reward_list)
plt.title("Reward")
plt.xlabel("Episode")
plt.ylabel("Reward")
plt.savefig("reinforce_cartpole_reward.png")
plt.show()

env.close()
