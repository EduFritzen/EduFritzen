package br.ufsm.eduardo;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.*;
import org.openqa.selenium.*;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;
import java.util.List;
import java.util.Random;

public class UcsdSiteTest {

    private static WebDriver driver;

    @BeforeAll
    public static void setUp() {
        System.setProperty("webdriver.chrome.driver", "C:\\selenium webdriver\\ChromeDriver\\chromedriver-win64//chromedriver.exe");
        driver = new ChromeDriver(); 
        driver.manage().window().maximize(); // Maximiza a janela do navegador
        driver.manage().deleteAllCookies(); // Limpa todos os cookies
        driver.manage().timeouts().implicitlyWait(Duration.ofMillis(10000)); // Define um tempo de espera implícito
    }

    @AfterAll
    public static void tearDown() {
        driver.quit(); // Fecha o navegador e encerra a sessão do WebDriver
    }

    @BeforeEach
    public void navigateToSite() {
        driver.get("https://www.ucsd.edu"); // Navega para a página principal do site UCSD
    }

    @Test
    public void testUrl() {
        String actualURL = driver.getCurrentUrl(); // Obtém a URL atual
        System.out.println("O nome da URL eh: " + actualURL); // Imprime a URL atual
        assertEquals(actualURL, "https://www.ucsd.edu/"); // Verifica se a URL é a esperada
    }
    
    // Testa se o título da página é o esperado
    @Test
    public void testTitle() {
        String title = driver.getTitle(); // Obtém o título da página
        assertEquals("University of California San Diego", title); // Verifica se o título é o esperado
        System.out.println(title); // Imprime o título no console
    }

    // Testa se o ícone de pesquisa está visível
    @Test
    public void testSearchButton() {
        WebElement searchButton = driver.findElement(By.className("search-icon")); // Encontra o ícone de pesquisa
        assertTrue(searchButton.isDisplayed()); // Verifica se ele está visível
    }

    // Testa a funcionalidade da caixa de pesquisa
    @Test
    public void testSearchBox() {
        WebElement searchIcon = driver.findElement(By.className("search-icon")); // Encontra o ícone de pesquisa
        searchIcon.click(); // Clica no ícone de pesquisa

        WebElement searchBox = driver.findElement(By.name("q")); // Encontra a caixa de pesquisa
        assertNotNull(searchBox); // Verifica se a caixa de pesquisa está presente

        searchBox.sendKeys("computer science"); // Digita na caixa de pesquisa

        WebElement searchButton = driver.findElement(By.className("search-icon")); // Encontra o botão de pesquisa
        searchButton.click(); // Clica no botão de pesquisa

        assertTrue(driver.getTitle().contains("Search Results")); // Verifica se o título da página contém "Search Results"
    }

    // Testa se o botão "Search UC San Diego" está selecionado
    @Test
    public void testRadioButton() {
        WebElement radioButton = driver.findElement(By.id("searchUCSD")); // Encontra o botão de rádio "Search UCSD"
        assertTrue(radioButton.isSelected()); // Verifica se está selecionado
    }

    // Testa se o carrossel principal está visível e contém itens
    @Test
    public void testMainCarousel() {
        WebElement carousel = driver.findElement(By.id("heroslider")); // Encontra o carrossel principal
        assertTrue(carousel.isDisplayed()); // Verifica se está visível

        List<WebElement> carouselItems = carousel.findElements(By.className("item")); // Encontra os itens do carrossel
        assertTrue(carouselItems.size() > 0); // Verifica se há itens no carrossel
    }

    // Testa se os cabeçalhos de seção (h2) estão visíveis e imprime seus textos
    @Test
    public void testSectionHeaders() {
        List<WebElement> headers = driver.findElements(By.tagName("h2")); // Encontra os cabeçalhos de seção (h2)
        assertTrue(headers.size() > 0); // Verifica se há cabeçalhos

        for (WebElement header : headers) {
            assertTrue(header.isDisplayed()); // Verifica se o cabeçalho está visível
            System.out.println(header.getText()); // Imprime o texto do cabeçalho
        }
    }

    // Testa se os links no rodapé estão visíveis e imprime seus textos e URLs
    @Test
    public void testFooterLinks() {
        List<WebElement> footerLinks = driver.findElements(By.cssSelector(".footer-links a")); // Encontra os links no rodapé
        assertTrue(footerLinks.size() > 0); // Verifica se há links

        for (WebElement link : footerLinks) {
            assertTrue(link.isDisplayed()); // Verifica se o link está visível
            System.out.println(link.getText() + ": " + link.getAttribute("href")); // Imprime o texto e a URL do link
        }
    }

    // Testa se a imagem com o logo da UCSD está visível e imprime o URL da imagem
    @Test
    public void testImagePresence() {
        WebElement image = driver.findElement(By.cssSelector("img[src*='logo_UCSD']")); // Encontra a imagem com o logo da UCSD
        assertTrue(image.isDisplayed()); // Verifica se a imagem está visível
        System.out.println("Image source: " + image.getAttribute("src")); // Imprime a URL da imagem
    }
    
    @Test
    public void testSliderFunctionality() {
        WebElement slider = driver.findElement(By.className("slick-slider")); // Localiza o slider

        WebElement nextButton = slider.findElement(By.className("slick-next")); // Localiza o botão "next"
        WebElement prevButton = slider.findElement(By.className("slick-prev")); // Localiza o botão "prev"

        assertTrue(nextButton.isDisplayed()); // Verifica se o botão "next" está visível
        nextButton.click(); // Clica no botão "next"
        driver.manage().timeouts().implicitlyWait(Duration.ofMillis(3000)); // Espera um pouco para o slider mudar

        assertTrue(prevButton.isDisplayed()); // Verifica se o botão "prev" está visível
        prevButton.click(); // Clica no botão "prev"
        driver.manage().timeouts().implicitlyWait(Duration.ofMillis(3000)); // Espera um pouco para o slider mudar

        List<WebElement> sliderItems = slider.findElements(By.className("slick-slide")); // Encontra os itens do slider
        assertTrue(sliderItems.size() > 0); // Verifica se há itens no slider

        for (WebElement item : sliderItems) {
            if (item.isDisplayed()) {
                System.out.println(item.getText()); // Imprime o texto de cada slide
            }
        }
    }

    //Testa o expansor de Divisions and Schools no fundo e vai a uma nova pagina aleatoria
    @Test
    public void testExpander() {
    	String actualURL = driver.getCurrentUrl();
    	
    	//Expande o expansor Divisions and Schools
    	WebElement discoverExpander = driver.findElement(By.id("divisions-expand"));
    	assertNotNull(discoverExpander, "O discover expander nao foi encontrado");
    	discoverExpander.click();
    	
    	//Checa se há elementos no expansor
    	List<WebElement> dropupElements = driver.findElements(By.className("text-link-secondary"));
    	assertTrue(dropupElements.size() > 0, "Nao ha elementos no expansor de Divisons and Schools");
    	
    	//Vai a um dos links do expansor aleatoriamente
    	Random rand = new Random();
    	int aleatorio = rand.nextInt(15);
    	int i = 0;
    	for (WebElement newPage : dropupElements) {
    		if (i == aleatorio) {
    			newPage.click();
    	    	String socialSciencesUrl = driver.getCurrentUrl();
    	    	assertNotEquals(socialSciencesUrl, actualURL, "As paginas nao sao as mesmas");
    		}
    		i++;
    	}
    }

    //Abre uma aba para cada item de notícias
    @Test
    public void testTabs() {
        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(10));
        List<WebElement> newsItems = wait.until(ExpectedConditions.visibilityOfAllElementsLocatedBy(By.className("news-item"))); // Espera até que os itens de notícia sejam visíveis

        assertTrue(newsItems.size() > 0, "Nenhum item de notícia foi encontrado."); // Verifica se há itens de notícia

        for (WebElement link : newsItems) {
            String novoLink = link.getAttribute("href"); // Obtém o link do item de notícia
            System.out.println("Abrindo link: " + novoLink); // Imprime o link

            driver.switchTo().newWindow(WindowType.TAB); // Abre um novo tab
            driver.get(novoLink); // Navega para o link

            assertTrue(driver.getTitle().length() > 0, "O título da nova aba está vazio."); // Verifica se a página foi carregada

            driver.close(); // Fecha a aba
            driver.switchTo().window(driver.getWindowHandles().iterator().next()); // Volta para a aba original
        }
    }

    //Testa a funcionalidade da barra de navegação principal
    @Test
    public void navbarTest() {
    	String actualURL = driver.getCurrentUrl();
    	
    	//Checa se a barra de navegação principal está visível
    	WebElement barraPrincipal = driver.findElement(By.className("main-nav"));
    	assertTrue(barraPrincipal.isDisplayed(),"A barra principal nao esta visivel");
    	
    	//Checa se a barra de navegação secundária está visível (não deve estar)
    	WebElement barraMenor = driver.findElement(By.className("dropdown"));
    	assertFalse(barraMenor.isDisplayed(),"A barra secundaria esta visivel");
    	
    	//Checa a barra
    	List <WebElement> elementosBarra = barraPrincipal.findElements(By.className("nav-group"));
    	assertTrue(elementosBarra.size() > 0, "Barra nao contem elementos");
    	
    	
    	System.out.println(elementosBarra.size());
    	for (WebElement barraLink : elementosBarra) {
    		assertTrue(barraLink.isDisplayed(), "A barra nao esta visivel");
    		System.out.println(barraLink.getText());
    	}

    	//Vai ate um elemento aleatorio de alguma das listas e clica nele
    	Random rand = new Random();
    	int aleatorio = rand.nextInt(6);
    	int i = 0;
    	for (WebElement barraLink : elementosBarra) {
    		if (i == aleatorio) {
    			barraLink.click();
    			String newURL = driver.getCurrentUrl();
    			System.out.println("A nova pagina eh:" + newURL);
    			assertNotEquals(newURL, actualURL, "As paginas nao sao as mesmas");
    		}
    		i++;
    	}
    } 
    
    //Testa o carregamento da página de contatos
    @Test
    public void testContactPage() {
        WebElement contactLink = driver.findElement(By.linkText("Contact"));
        assertTrue(contactLink.isDisplayed(), "O link de Contato não está visível.");
        
        contactLink.click();
        
        // Espera a nova página carregar
        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(10));
        wait.until(ExpectedConditions.titleContains("Contact"));

        // Verifica se a página foi carregada com sucesso
        assertTrue(driver.getTitle().contains("Contact"), "A página de Contato não carregou corretamente.");

        // Verifica a presença das informações de contato
        WebElement contactInfo = driver.findElement(By.tagName("h1"));
        assertTrue(contactInfo.isDisplayed(), "As informações de contato não estão visíveis.");
    }
    
 // Testa a presença e funcionalidade dos links de navegação no menu principal via abas
    @Test
    public void buttonsTest() {
        // Encontra todos os botões com a classe "btn-default"
        List<WebElement> botoes = driver.findElements(By.className("btn-default"));
        // Verifica se há botões na página
        assertNotNull(botoes.size() > 0, "Não há botões na página");

        // Para cada botão encontrado
        for (WebElement botao : botoes) {
            // Imprime o texto do botão no console
            System.out.println("Checando o botão: " + botao.getText());
            // Verifica se o botão está habilitado
            assertTrue(botao.isEnabled(), "Botão não funciona!");
        }
    }
   
}
