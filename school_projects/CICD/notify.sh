#!/bin/bash
TELEGRAM_BOT_TOKEN="xxxx"
TELEGRAM_USER_ID="xxxxx"
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"

TEXT="Pipeline status: $1%0A%0A$CI_PROJECT_NAME ($CI_COMMIT_REF_SLUG)%0A$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/"
TIME="10"

curl --silent --max-time $TIME --data "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL 