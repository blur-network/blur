#!/bash

function create_wallet {
    wallet_name=$1
    echo 0 | blur-wallet-cli  --testnet --daemon-address localhost:13894 --generate-new-wallet $wallet_name --password "" --restore-height=1
}


create_wallet wallet_01
create_wallet wallet_02
create_wallet wallet_03
create_wallet wallet_04
create_wallet wallet_05
create_wallet wallet_06

# create_wallet wallet_m


