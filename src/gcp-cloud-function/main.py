import logging
import os
import re
from google.cloud import bigquery
import base64
import json

logging.basicConfig(format='%(name)s - %(levelname)s - %(message)s', level=logging.INFO)
logger = logging.getLogger(__name__)



def processMessage(event, context):
    dataset = '<dataset name here. e.g. test1>'
    table = '<fully qualified table name here. e.g. gcp-project-id.datasetName.tableName>'
    message = base64.b64decode(event['data']).decode('utf-8')
    try:
        logger.info('Message received: %s', str(message))
        # Load JSON string to dictionary
        jdata = json.loads(message)
        client = bigquery.Client()
        dataset_ref = client.dataset(dataset)
        # check if dataset exists, otherwise create
        try:
            client.get_dataset(dataset_ref)
        except Exception:
            logging.warn('Creating dataset: %s' % (dataset))
            client.create_dataset(dataset_ref)

        job_config = bigquery.LoadJobConfig()
        job_config.autodetect = True
        load_job = client.load_table_from_json([jdata], table, job_config=job_config)
        logger.info('Load job: %s [%s]' % (
            load_job.job_id,
            load_job.result()
        ))
    except Exception as e:
        logger.info('Error-unable-to-process message:%s exception:%s', str(message), e)