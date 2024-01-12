# Start from the latest Ubuntu version
FROM ubuntu:latest

# Update the system and install utils
RUN apt-get update && apt-get install -y \
    valgrind \
    build-essential \
    binutils \
    clang-12 \
    git \
    zsh \
    wget \
    curl \
    libreadline-dev \
    libreadline8

# Download and install the latest version of make
RUN wget http://ftp.gnu.org/gnu/make/make-4.3.tar.gz && \
    tar -xvzf make-4.3.tar.gz && \
    cd make-4.3 && \
    ./configure && \
    make && \
    make install

# Install oh-my-zsh
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" || true
RUN echo "source $HOME/.oh-my-zsh/oh-my-zsh.sh" >> $HOME/.zshrc
SHELL ["/bin/zsh", "-c"]

# Set the working directory in the container to /app
WORKDIR /app

# Copy the act file to the Docker image
COPY ./act /app/act

# Change the permissions of the act file to make it executable
RUN chmod +x /app/act

