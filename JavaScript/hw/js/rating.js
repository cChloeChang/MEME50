let imgs = document.querySelectorAll("img.star");
let currentRating = 0; // 儲存當前評分

// 抓<div class="wrap">，並插入 ratingMessage
const wrapContainer = document.querySelector(".wrap");
const ratingMessage = document.createElement("div");
ratingMessage.style.textAlign = "center";
ratingMessage.style.marginTop = "10px";
ratingMessage.style.fontSize = "20px";
ratingMessage.style.fontFamily = "微軟正黑體";
ratingMessage.textContent = "評分為 0，給 0 顆星";
wrapContainer.appendChild(ratingMessage);

for (let img of imgs) {
    img.addEventListener("mouseover", mouseover);
    img.addEventListener("mouseout", mouseout);
    img.addEventListener("click", click);
    img.addEventListener("dblclick", resetRating);
}

function mouseover() {
    let number = parseInt(this.id.substring(7)); // 獲取星星的數字
    for (let i = 0; i < number; i++) {
        imgs[i].src = "images/star2.png"; // 改變星星為亮的圖片
    }
}

function mouseout() {
    for (let i = 0; i < imgs.length; i++) {
        if (i < currentRating) {
            imgs[i].src = "images/star2.png"; // 保持亮的星星
        } else {
            imgs[i].src = "images/star.png";
        }
    }
}

function click() {
    currentRating = parseInt(this.id.substring(7)); // 更新當前評分，starimg"1"數字部分從第5個字元開始
    for (let i = 0; i < imgs.length; i++) {
        imgs[i].src = i < currentRating ? "images/star2.png" : "images/star.png";
    }
    // console.log(`當前評分: ${currentRating}`);
    ratingMessage.textContent = `評分為 ${currentRating}，給 ${currentRating} 顆星`;
}

function resetRating() {
    currentRating = 0; // 重置評分
    for (let i = 0; i < imgs.length; i++) {
        imgs[i].src = "images/star.png"; // 全部還原為暗的星星
    }
    ratingMessage.textContent = `評分為 ${currentRating}，給 ${currentRating} 顆星`;
}