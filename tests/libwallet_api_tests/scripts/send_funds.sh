#!/bash

function send_funds {
    local amount=$1
    local dest=$(cat "$2.address.txt")

    blur-wallet-cli --wallet-file wallet_m --password "" \
        --testnet  --daemon-address localhost:13894  --log-file wallet_m.log \
        --command transfer $dest $amount 
}


function seed_wallets {
    local amount=$1
    send_funds $amount wallet_01
    send_funds $amount wallet_02
    send_funds $amount wallet_03
    send_funds $amount wallet_04
    send_funds $amount wallet_05
    send_funds $amount wallet_06
}

seed_wallets 1
seed_wallets 2
seed_wallets 5
seed_wallets 10
seed_wallets 20
seed_wallets 50
seed_wallets 100



