1 этап. Ожидание и схема:

Описание схемы:

Используются плата Arduino UNO, ультразвуковой датчик HC-SR04 (TRIG на D9, ECHO на D10), кнопка пуска на пине D2 (с подтяжкой INPUT_PULLUP), три светодиода индикации расстояния (красный на D13, желтый на D12, зеленый на D11), а также пара светодиодов имитации мотора - синий (пин D5, IN1 - движение вперёд) и фиолетовый (пин D6, IN2 - реверс/назад). Для визуализации сигналов задействован логический анализатор Wokwi Logic вместо L298N.

Таблица истинности:

<img width="1600" height="927" alt="Tablitsa istina" src="https://github.com/user-attachments/assets/657fedd8-6631-4e41-b281-90c3046ccb3b" />


Ожидаемое поведение:

< 20 см (Опасная зона): Система останавливается, горит красный светодиод расстояния, сигналы управления отключены.

20–50 см (Средняя зона, включая 35 см): Имитация движения вперёд со средней скоростью, горит желтый светодиод и синий светодиод (ШИМ = 120).

Если >50 см (Свободная зона): Имитация движения вперёд на максимальной скорости, горит зеленый светодиод и синий светодиод (ШИМ = 255).

Правило безопасного состояния:

При потере эхо-сигнала от датчика (pulseIn() возвращает тайм-аут 0) система мгновенно переходит в защитный режим: все светодиоды гаснут, а управляющие выводы принудительно обнуляются.

2 этап. Базовые испытания:

Была собран вот такой стенд в Wokwi:

<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/737b869c-bdc8-4830-a971-6e65eae2c035" />

Как было сказано выше, из за того что не было компонентов такие как L298N и DC-motor, пришлось заменить Быих соответсвенно на Wokwi logic и два светодиода (Синий = движение вперед, фиолетовый = движение назад/реверс).

Была реелизована логика управления:

<img width="620" height="127" alt="logica upravlenia" src="https://github.com/user-attachments/assets/e21775ad-ac31-4116-8004-10ee3a5d0516" />

<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/806ccadc-c9e8-447a-98fd-95761f3cf74f" />

<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/6bdc1ca5-978f-408e-a076-f50edf3b5356" />

<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/cc003b14-6b4a-4537-8ca7-556645ff80fa" />

Испытания и таблица:

<img width="882" height="454" alt="Tablitsa ispitanii" src="https://github.com/user-attachments/assets/70caccee-6e77-4032-a8a1-ddd853a7ef6d" />

1 испытание:
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/deb1b271-1ba8-4c31-acfa-48c80117b188" />

2 испытание:
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/dc8fdd55-05ba-4e06-b17a-7fed35788dda" />

3 испытание:
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/69967279-753c-449f-abd5-8d11140e7925" />

4 испытание:
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/2886d728-376f-4a82-a466-2359827d1a99" />

5 испытание:
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/5f1bc6da-897d-488b-a075-86cada3a1f2d" />

6 испытание:
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/bf42a869-6708-42db-9103-5d5d0e6dad75" />

7 испытание:
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/77d9a937-c5a1-425a-b86c-2ddbb1bfa891" />
Я убрала провод Echo между HC-SR04 и Arduino, чтобы показать как работат. Затем вернула провод обратно.

8 испытание:
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/d6a7a6cb-bb1b-4fef-a423-910605f53a9b" />
Я поменяла в коде управляющие уровние (HIGH/LOW) местами для синего и фиолетового светодиодов. Тоесть заменила на такое на расстоянии от 20-50:

digitalWrite(motorForwardPin, LOW);

digitalWrite(motorReversePin, HIGH); 
