# PROJ_ULTRASONIC
Реализация работы ультразвукового датчика на базе МК STM32F0DISCOVERY с выводом результата на дисплей NOKIA 5110 при помощи библиотеки CMSIS. Также в проекте есть звуковое оповещение при приближении объекта и свечение светодиодами на разных расстояниях.
Для отображения русского текста необходимо, чтобы файл main.c был в кодировкой Windows 1251. Редактировать и сохранять файл (изменить русский текст при выводе на дисплей) нужно в сторонних редакторах, например Notepad++. Затем открыть Keil и прошить. Такая процедура нужна, потому, что Keil не может выводить русский текст. В других IDE такого может и не быть. Не проверял.
