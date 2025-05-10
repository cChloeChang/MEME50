document.addEventListener('DOMContentLoaded', async () => {
    // 側邊欄折疊
    document.getElementById('sidebarToggle').addEventListener('click', function() {
        document.querySelector('.sidebar').classList.toggle('open');
    });

    // Tab 切換功能
    window.openTab = function(evt, tabName) {
        var i, tabcontent, tablinks;
        tabcontent = document.getElementsByClassName("tabcontent");
        for (i = 0; i < tabcontent.length; i++) {
            tabcontent[i].style.display = "none";
        }
        tablinks = document.getElementsByClassName("tablinks");
        for (i = 0; i < tablinks.length; i++) {
            tablinks[i].classList.remove("active");
        }
        document.getElementById(tabName).style.display = "block";
        evt.currentTarget.classList.add("active");

        if (tabName === 'accessLogTab') loadAccessLogs();
    };

    // 預設打開首頁tab
    document.getElementById("defaultTab").click();

});