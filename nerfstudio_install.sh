#!/bin/bash
#SBATCH -p gpi.compute        # Partition to submit to
#SBATCH --mem=10G             # Max CPU Memory 
#SBATCH --gres=gpu:1
#SBATCH --time=1:00:00
#SBATCH --nodelist=gpic12
#SBATCH --output=logs_installing_nerfstudio.out          # output file name
#SBATCH --error=logs_installing_nerfstudio.out           # error file name (same to watch just one file)


#echo "Creating conda environtment..."
#conda create --name nerfstudio_prova -y python=3.8

#echo ""
echo "Upgrading pip..."
#conda activate nerfstudio
python -m pip install --upgrade pip

echo ""
echo "Installing PyTorch..."
pip uninstall torch torchvision functorch tinycudann
pip install torch==2.0.1+cu118 torchvision==0.15.2+cu118 --extra-index-url https://download.pytorch.org/whl/cu118

echo ""
echo "Installing cuda-toolkit..."
conda install -c "nvidia/label/cuda-11.8.0" cuda-toolkit

echo ""
echo "Installing ninja and tiny-cuda-nn..."
pip install ninja git+https://github.com/NVlabs/tiny-cuda-nn/#subdirectory=bindings/torch

echo ""
echo "Installing nerfstudio..."
pip install nerfstudio
