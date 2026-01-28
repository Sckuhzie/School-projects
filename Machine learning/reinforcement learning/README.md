# TD1 : Hands on reinforcement learning

## Installation

This code is made with python 3.12.9. To install all the dependancies, just run the following command :

`pip install -r requirements.txt`

## Reinforce cartpole

The code to train the model on the environment of the cartpole is in the file [reinforce_cartpole.py](reinforce_cartpole.py).

Here is the graph showing the evolution of the reward accross episodes :

![Reinforce Cartpole Reward](readme_ressource/reinforce_cartpole_reward.png)

The evaluation of the agent is made with the code in the file [evaluate_reinforce_cartpole.py](evaluate_reinforce_cartpole.py). The agent has a success rate of 100% accross all evaluations.

You can view a run of the model in the file [eval_cartpole.py](reinforce_cartpole.py).

## A2C SB3 cartpole

The code is in the file [a2c_sb3_cartpole.py](a2c_sb3_cartpole.py) (On my machine (Windows), I must run python as an administrator to make the code working).

Example video of the model performance : ![A2C_cartpole](readme_ressource/a2c_cartpole.mp4)

The model is available on Hugging Face : (https://huggingface.co/Sckuhzie-ECL/hands-on-rl)

The model and metrics are available on weight and bias here : https://wandb.ai/paul-lacroix-centrale-lyon/sb3/runs/fatk5yj1?nw=nwuserpaullacroix

If it is not available the report with the graph is [here](report_cartpole.pdf)

## A2C SB3 Panda Reach

The code is in the file [a2c_sb3_panda_reach.py](a2c_sb3_panda_reach.py) (same as above, I have to run it as an administrator).

Example video of the model performance : ![A2C_panda-reach](readme_ressource/a2c_panda-reach.mp4)

The model and metrics are available here : (https://huggingface.co/Sckuhzie-ECL/hands-on-rl)
(https://wandb.ai/paul-lacroix-centrale-lyon/sb3/runs/2smlo60r?nw=nwuserpaullacroix)

If it is not available the report with the graph is [here](report_panda-reach.pdf)
