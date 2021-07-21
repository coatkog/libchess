# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.187.0/containers/ubuntu/.devcontainer/base.Dockerfile

ARG VARIANT="focal"
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    build-essential \
    cmake \
    clangd-12

RUN ln /usr/bin/clangd-12 /usr/bin/clangd
