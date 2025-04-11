const slides = [
    {
        // subtitle: "The big window",
        logo: "./images/adidas_logo.png",
        title: "Adidas",
        description: "Adidas為一專注於設計、開發與行銷的國際知名運動品牌，致力研發專業鞋款、服飾及配件，並以成為世界級運動專業領導品牌為目標。<br>同時通過當代年輕文化視角，融合源於運動場上的創造力與勇氣，積極鼓勵大膽探索，勇於發揮原創力。",
        image: "./images/adidas.jpg",
        link: "https://www.adidas.com.tw/"
    },
    {
        logo: "./images/nb_logo.png",
        title: "New Balance",
        description: "我們致力於遠比運動鞋重要的事。我們全力支持充滿熱情且無畏無懼的每個人。我們重視提升運動的水平。我們在人類和地球之間做著正確的事。我們努力不懈，推動世界各地的社區作出有意義的改變。We Got Now.",
        image: "./images/nb.jpg",
        link: "https://www.newbalance.com.tw/%E5%84%AA%E6%83%A0%E6%B4%BB%E5%8B%95/2025-lny-5000get500/?gad_source=1&gclid=EAIaIQobChMIitmb0Ln_igMVZoC5BR3Low6tEAAYASAAEgI-j_D_BwE"
    },
    {
        logo: "./images/nike_logo.png",
        title: "Nike",
        description: "我們的使命是：將靈感與創新帶給世上每位運動員。<br>只要有身體，人人都是運動員。",
        image: "./images/nike.jpg",
        link: "https://www.nike.com/tw/men?cp=23805160247_search_%7Ctw%7CCore+Brand+-+Core+Brand+-+General+-+CH_CH%7CGOOGLE%7Cnike&gad_source=1&ds_rl=1300698&gclid=EAIaIQobChMIwsfmstKAiwMVXNoWBR34_SYbEAAYASAAEgJHMfD_BwE&gclsrc=aw.ds"
    },
    {
        logo: "./images/asics_logo.png",
        title: "ASICS",
        description: "生於一次世界大戰後的鬼塚先生，有鑒於二次大戰後社會低迷氣氛，決定創辦一個能夠給與年輕人夢想的事業。\
        他深刻體會古羅馬詩人Juvenal所說的一句名言“健全的精神源自健康的體魄（Anima Sana In Corpore Sano＝A Sound Mind in a Sound Body）”。<br>因此決定以此為目標，終身投入奉獻運動事業；期望透過運動，協助解決青少年問題，於是開始生產鞋子，鬼塚株式會社也因此誕生。",
        image: "./images/asics.jpg",
        link: "https://www.asics.com.tw/?lang=zh-TW"
    },
    {
        logo: "./images/puma_logo.png",
        title: "PUMA",
        description: "PUMA是全球首屈一指的運動領導品牌，設計開發並銷售製造各種鞋類、服裝以及配件產品。<br>PUMA的專業運動與運動時尚產品系列涉及跑步、訓練、健身、籃球、足球、高爾夫、賽車，同時也與世界知名設計品牌共同合作開發商品，創作出更多新穎的運動時尚產品。",
        image: "./images/puma.jpg",
        link: "https://tw.puma.com/"
    }
];

let currentSlide = 0;
let isPlaying = true;
// const subtitleEl = document.getElementById("subtitle");
const logoEl = document.getElementById("logo");
const titleEl = document.getElementById("title");
const descriptionEl = document.getElementById("description");
const imageEl = document.getElementById("image");
const linkEl = document.getElementById("link");
const imageLinkEl = document.getElementById("image-link");
const progressEl = document.getElementById("progress");

const updateSlide = function () {
    const slide = slides[currentSlide];
    // subtitleEl.textContent = slide.subtitle;
    logoEl.src = slide.logo;
    titleEl.textContent = slide.title;
    descriptionEl.innerHTML = slide.description;
    imageEl.style.backgroundImage = `url('${slide.image}')`;
    linkEl.href = slide.link;
    imageLinkEl.href = slide.link;
    progressEl.textContent = `${currentSlide + 1} / ${slides.length}`;
};

const nextSlide = function () {
    currentSlide = (currentSlide + 1) % slides.length;
    updateSlide();
};

const prevSlide = function () {
    currentSlide = (currentSlide - 1 + slides.length) % slides.length;
    updateSlide();
};

let interval = setInterval(nextSlide, 3500);

document.getElementById("next").addEventListener("click", nextSlide);
document.getElementById("prev").addEventListener("click", prevSlide);
document.getElementById("pause").addEventListener("click", () => {
    if (isPlaying) {
        clearInterval(interval);
        isPlaying = false;
        // document.getElementById("pause").textContent = "Play";
        document.getElementById("pause").innerHTML = "<i class='fa-solid fa-play'></i>";
    } else {
        interval = setInterval(nextSlide, 3000);
        isPlaying = true;
        // document.getElementById("pause").textContent = "Pause";
        document.getElementById("pause").innerHTML = "<i class='fa-solid fa-pause'></i>";
    }
});

updateSlide();