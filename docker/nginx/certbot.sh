#!/bin/bash

TOKEN=""
CHAT_ID=""

if [ -z "$CERTBOT_COUNTER" ]; then
  CERTBOT_COUNTER=0
fi
((CERTBOT_COUNTER++))
export CERTBOT_COUNTER

MESSAGE="[SERVER] CertBot: Run certbot.sh. CERBOT_COUNTER = $CERTBOT_COUNTER. $(date)"
curl -s -X POST "https://api.telegram.org/bot$TOKEN/sendMessage" -d "chat_id=$CHAT_ID&text=$MESSAGE"
echo $MESSAGE >> /var/log/cron.log
