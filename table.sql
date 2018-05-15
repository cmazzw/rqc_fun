-- 创建sqlite阈值表

CREATE TABLE qc(
MON CHAR(3) PRIMARY KEY NOT NULL, --月份
WIND_MIN CHAR(4)  NOT NULL,       --最小风
WIND_MAX CHAR(4)  NOT NULL,       --最大风
RAIN_MIN CHAR(5)  NOT NULL,       --最小降雨量
RAIN_MAX CHAR(5)  NOT NULL,       --最大降雨量
TEMP_MIN CHAR(6)  NOT NULL,       --最小温度
TEMP_MAX CHAR(6)  NOT NULL,       --最大温度
PRES_MIN CHAR(6)  NOT NULL,       --最小气压
PRES_MAX CHAR(6)  NOT NULL,       --最大气压
G_TEMP_MIN CHAR(5)  NOT NULL,     --最小地温
G_TEMP_MAX CHAR(5)  NOT NULL,     --最大地温
S_PRES_MIN CHAR(6)  NOT NULL,     --最小海平面气压
S_PRES_MAX CHAR(6)  NOT NULL      --最大海平面气压
);


-- 阈值赋值

