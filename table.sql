-- ����sqlite��ֵ��

CREATE TABLE qc(
MON CHAR(3) PRIMARY KEY NOT NULL, --�·�
WIND_MIN CHAR(4)  NOT NULL,       --��С��
WIND_MAX CHAR(4)  NOT NULL,       --����
RAIN_MIN CHAR(5)  NOT NULL,       --��С������
RAIN_MAX CHAR(5)  NOT NULL,       --�������
TEMP_MIN CHAR(6)  NOT NULL,       --��С�¶�
TEMP_MAX CHAR(6)  NOT NULL,       --����¶�
PRES_MIN CHAR(6)  NOT NULL,       --��С��ѹ
PRES_MAX CHAR(6)  NOT NULL,       --�����ѹ
G_TEMP_MIN CHAR(5)  NOT NULL,     --��С����
G_TEMP_MAX CHAR(5)  NOT NULL,     --������
S_PRES_MIN CHAR(6)  NOT NULL,     --��С��ƽ����ѹ
S_PRES_MAX CHAR(6)  NOT NULL      --���ƽ����ѹ
);


-- ��ֵ��ֵ

