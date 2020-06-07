var canvas = document.getElementById("canvas"); //Получение холста из DOM
var ctx = canvas.getContext("2d"); //Получение контекста — через него можно работать с холстом
 
var scale = 0.1; //Масштаб машин
 
Resize(); // При загрузке страницы задаётся размер холста
 
window.addEventListener("resize", Resize); //При изменении размеров окна будут меняться размеры холста
 
window.addEventListener("keydown", function (e) { KeyDown(e); }); //Получение нажатий с клавиатуры
 
var objects = []; //Массив игровых объектов
var roads = []; //Массив с фонами
 
var player = null; //Объект, которым управляет игрок, — тут будет указан номер объекта в массиве objects
 
function Start()
{
    timer = setInterval(Update, 1000 / 60); //Состояние игры будет обновляться 60 раз в секунду — при такой частоте обновление происходящего будет казаться очень плавным
}
 
function Stop()
{
    clearInterval(timer); //Остановка обновления
}
 
function Update() //Обновление игры
{
    Draw();
}
 
function Draw() //Работа с графикой
{
    ctx.clearRect(0, 0, canvas.width, canvas.height); //Очистка холста от предыдущего кадра
}
 
function KeyDown(e)
{
    switch(e.keyCode)
    {
        case 37: //Влево
            break;
 
        case 39: //Вправо
            break;
 
        case 38: //Вверх
            break;
 
        case 40: //Вниз
            break;
 
        case 27: //Esc
            break;
    }
}
 
function Resize()
{
    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;
}
