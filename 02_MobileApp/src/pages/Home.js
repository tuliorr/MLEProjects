// Imports
import React, { useState, useEffect } from "react";
import { useFonts } from "expo-font";
import Carousel from "react-native-snap-carousel";
import { StyleSheet, View, Text, Image, Dimensions, TouchableOpacity, ScrollView, } from "react-native";

// Imagens
import Filter from "../../assets/filterIcon.png";
import Exit from "../../assets/exitIcon.png";
import Song from "../../assets/songIcon.png";
import Ticket from "../../assets/ticketIcon.png";
import More from "../../assets/moreIcon.png";
import Area from "../../assets/areaIcon.png";
import Music from "../../assets/musicIcon.png";
import Sport from "../../assets/sportIcon.png";
import Location from "../../assets/locationIcon.png";
import Right from "../../assets/rightIcon.png";
import recommend_bitmap1 from "../../assets/recommend_bitmap1.png";
import recommend_bitmap2 from "../../assets/recommend_bitmap2.png";
import Collection_bitmap1 from "../../assets/collection_bitmap1.png";
import Collection_bitmap2 from "../../assets/collection_bitmap2.png";
import Coming_bitmap1 from "../../assets/coming_bitmap1.png";
import Coming_bitmap2 from "../../assets/coming_bitmap2.png";
import Coming_bitmap3 from "../../assets/coming_bitmap3.png";

// Componentes
import Bottombar from "../components/bottombar";

// Constante
const WIDTH = Dimensions.get("window").width;

// Cartões de recomendações de eventos esportivos
const RECOMMEND_CARDS = [
    {
        date: "Sexta, 20/10, 21:00",
        title: "Jogos Olímpicos",
        type: "Olímpiadas",
        price: "R$150",
        image: recommend_bitmap1,
    },
    {
        date: "Domingo, 12/11, 15:00",
        title: "Jogo de Abertura",
        type: "Copa do Mundo",
        price: "R$200",
        image: recommend_bitmap2,
    },
];

// Cartões de grupos de eventos esportivos
const COLLECTION_CARDS = [
    {
        title: "São Silvestre",
        type: "Maratona",
        image: Collection_bitmap1,
    },
    {
        title: "Campeonato Brasileiro",
        type: "Futebol",
        image: Collection_bitmap2,
    },
];

// Cartões de grupos gerais
const DISCOVER_CARDS = [
    {
        title: "Seus Eventos",
        image: Area,
        color: "#FFC3D8",
        textColor: "#FC1055",
    },
    {
        title: "Hinos",
        image: Music,
        color: "#ACCCFF",
        textColor: "#5798FF",
    },
    {
        title: "Esportes",
        image: Sport,
        color: "#FFC8AC",
        textColor: "#E69960",
    },
];

// Cartões de eventos futuros
const COMING_CARDS = [
    {
        date: "28",
        dayWeek: "Qua",
        events: [
            {
                title: "Campeonato Mundial",
                type: "Natação",
                price: "R$120",
                image: Coming_bitmap1,
            },
            {
                title: "Campeonato Mundial",
                type: "Natação",
                price: "R$120",
                image: Coming_bitmap1,
            },
        ],
    },
    {
        date: "29",
        dayWeek: "Qui",
        events: [
            {
                title: "NBA - Liga de Basquete",
                type: "Basquete",
                price: "R$90",
                image: Coming_bitmap3,
            },
            {
                title: "Jogo 1",
                type: "Basquete",
                price: "€40 - €90",
                image: Coming_bitmap3,
            },
            {
                title: "Jogo 2",
                type: "Basquete",
                price: "R$90",
                image: Coming_bitmap1,
            },
            {
                title: "Jogo 3",
                type: "Basquete",
                price: "R$90",
                image: Coming_bitmap2,
            },
        ],
    },
];

// Home
export default function Home() {
    
    const [recommend, setRecommend] = useState([]);
    const [collectionCards, setCollectionCards] = useState([]);
    const [discoverCards, setDiscoverCards] = useState([]);
    const [comingCards, setComingCards] = useState([]);

    const [loaded, error] = useFonts({
        "Work-Sans-Bold": require("../../assets/fonts/WorkSans-Bold.ttf"),
        "Work-Sans-SemiBold": require("../../assets/fonts/WorkSans-SemiBold.ttf"),
        "Nunito-ExtraBold": require("../../assets/fonts/Nunito-ExtraBold.ttf"),
    });

    useEffect(() => {
        setRecommend(RECOMMEND_CARDS);
        setCollectionCards(COLLECTION_CARDS);
        setDiscoverCards(DISCOVER_CARDS);
        setComingCards(COMING_CARDS);
    }, []);

    const recommended_slide = ({ item, index }) => {
        return (
            <View style={recommended.card}>
                <Image source={item.image} style={recommended.cardImage} />
                <TouchableOpacity style={recommended.exit}>
                    <View style={recommended.exitIcon}>
                        <Image source={Exit} style={recommended.exitImage} />
                    </View>
                </TouchableOpacity>
                <TouchableOpacity>
                    <Text style={recommended.cardDate}>{item.date}</Text>
                    <Text style={recommended.cardTitle}>{item.title}</Text>
                    <View style={recommended.cardDescription}>
                        <View style={recommended.song}>
                            <Image
                                source={Song}
                                style={recommended.descriptionIcon}
                            />
                            <Text style={recommended.description}>
                                {item.type}
                            </Text>
                        </View>
                        <View style={recommended.ticket}>
                            <Image
                                source={Ticket}
                                style={recommended.descriptionIcon}
                            />
                            <Text style={recommended.description}>
                                {item.price}
                            </Text>
                        </View>
                    </View>
                </TouchableOpacity>
            </View>
        );
    };

    const collections_slide = ({ item, index }) => {
        return (
            <TouchableOpacity style={collections.card}>
                <View>
                    <Image source={item.image} style={collections.cardImage} />
                    <Text style={collections.cardTitle}>{item.title}</Text>
                    <View style={collections.description}>
                        <Image
                            source={Song}
                            style={collections.descriptionIcon}
                        />
                        <Text style={collections.descriptionText}>
                            {item.type}
                        </Text>
                    </View>
                </View>
                <View>
                    <TouchableOpacity style={collections.more}>
                        <Text style={collections.moreText}>Learn more</Text>
                        <Image source={More} style={collections.moreIcon} />
                    </TouchableOpacity>
                </View>
            </TouchableOpacity>
        );
    };

    const coming_events = comingCards.map((item, index) => {
        const more = comingCards[index].events.length - 1;
        let last = false;
        if (comingCards.length === index + 1) {
            last = true;
        }
        return (
            <View
                key={index}
                style={
                    last ? [coming.event, { marginBottom: "30%" }] : coming.event
                }
            >
                <View style={coming.day}>
                    <View style={coming.date}>
                        <Text style={coming.dateDay}>{item.date}</Text>
                        <Text style={coming.dateWeek}>{item.dayWeek}</Text>
                    </View>
                </View>
                <View style={coming.eventCards}>
                    <TouchableOpacity style={coming.eventMainCard}>
                        <Image
                            source={item.events[0].image}
                            style={coming.eventMainImage}
                        />
                        <Text style={coming.eventTitle}>
                            {item.events[0].title}
                        </Text>
                        <View style={coming.eventDescription}>
                            <Image
                                source={Song}
                                style={coming.descriptionIcon}
                            />
                            <Text style={coming.descriptionType}>
                                {item.events[0].type}
                            </Text>
                            <Image
                                source={Ticket}
                                style={coming.descriptionIcon}
                            />
                            <Text style={coming.descriptionPrice}>
                                {item.events[0].price}
                            </Text>
                        </View>
                    </TouchableOpacity>
                    <View style={coming.eventSubCard}>
                        <Image
                            source={item.events[1].image}
                            style={coming.eventSubImage}
                        />
                        <View style={coming.eventMore}>
                            <Text style={coming.eventMoreText}>
                                {more} Events more
                            </Text>
                            <Image source={More} style={coming.eventMoreIcon} />
                        </View>
                    </View>
                </View>
            </View>
        );
    });

    if (!loaded) {
        return <Text>Carregando...</Text>;
    } else {
        return (
            <>
                <View style={styles.header}>
                    <Text style={styles.logo}>Home</Text>
                </View>
                <ScrollView>
                    <View style={recommended.index}>
                        <View style={recommended.header}>
                            <Text style={recommended.title}>Próximos Eventos</Text>
                            <View style={recommended.filter}>
                                <Image
                                    source={Filter}
                                    style={recommended.image}
                                />
                            </View>
                        </View>
                        <Carousel
                            layout={"default"}
                            data={recommend}
                            renderItem={recommended_slide}
                            sliderWidth={Dimensions.get("window").width}
                            itemWidth={Dimensions.get("window").width * 0.84}
                            hasParallaxImages={true}
                        />
                    </View>
                    <View style={collections.index}>
                        <View style={collections.header}>
                            <Text style={collections.title}>Esportes</Text>
                        </View>
                        <Carousel
                            layout={"default"}
                            data={collectionCards}
                            renderItem={collections_slide}
                            sliderWidth={Dimensions.get("window").width}
                            itemWidth={Dimensions.get("window").width * 0.84}
                            hasParallaxImages={true}
                        />
                    </View>
                    <View style={discover.index}>
                        <View style={discover.header}>
                            <Text style={discover.title}></Text>
                        </View>
                        <ScrollView
                            horizontal
                            showsHorizontalScrollIndicator={false}
                        >
                            {discoverCards.map((item, index) => {
                                return (
                                    <TouchableOpacity key={index}>
                                        <View style={discover.card}>
                                            <View
                                                style={[
                                                    discover.icon,
                                                    {
                                                        backgroundColor:
                                                            item.color,
                                                    },
                                                ]}
                                            >
                                                <Image
                                                    source={item.image}
                                                    style={discover.iconImage}
                                                />
                                            </View>
                                            <Text
                                                style={[
                                                    discover.text,
                                                    {
                                                        color: item.textColor,
                                                    },
                                                ]}
                                            >
                                                {item.title}
                                            </Text>
                                        </View>
                                    </TouchableOpacity>
                                );
                            })}
                        </ScrollView>
                    </View>
                    <View style={coming.index}>
                        <View style={coming.header}>
                            <View style={coming.location}>
                                <Image
                                    source={Location}
                                    style={coming.locationIcon}
                                />
                                <Text style={coming.locationText}></Text>
                            </View>
                            <View style={coming.title}>
                                <Text style={coming.titleText}>Agenda</Text>
                                <View style={coming.titleIcon}>
                                    <Image
                                        source={Right}
                                        style={coming.iconImage}
                                    />
                                </View>
                            </View>
                        </View>
                        <View style={coming.eventMonth}>
                            <Text style={coming.eventMonthText}>Jul</Text>
                            {coming_events}
                        </View>
                    </View>
                </ScrollView>
                <View style={{ marginBottom: "20%" }} />
                <Bottombar />
            </>
        );
    }
}

//* CSS Global
const styles = StyleSheet.create({
    header: {
        display: "flex",
        justifyContent: "center",
        height: "9%",
        backgroundColor: "#FFF",
    },
    logo: {
        marginTop: "5%",
        textAlign: "center",
        lineHeight: 28,
        fontSize: 22,
        fontFamily: "Work-Sans-Bold",
    },
});

//* Seção de Recomendações
const recommended = StyleSheet.create({
    index: {
        marginTop: "8%",
        flexDirection: "column",
    },
    header: {
        marginHorizontal: "5%",
        flexDirection: "row",
        alignItems: "center",
        justifyContent: "space-between",
    },
    title: {
        lineHeight: 36,
        fontSize: 32,
        fontFamily: "Work-Sans-Bold",
        color: "#373A42",
    },
    filter: {
        backgroundColor: "#FFF",
        width: "8%",
        height: WIDTH * 0.07,
        display: "flex",
        justifyContent: "center",
        alignItems: "center",
        borderRadius: 90,
    },
    image: {
        height: WIDTH * 0.05,
        width: WIDTH * 0.05,
    },
    card: {
        marginTop: 29,
        height: "21%",
    },
    cardImage: {
        position: "absolute",
        width: "100%",
        height: "400%",
        borderRadius: 16,
    },
    cardDate: {
        color: "#FFF",
        marginTop: 140,
        marginLeft: "5%",
        marginBottom: "2%",
        fontSize: 14,
        lineHeight: 16,
        fontFamily: "Work-Sans-SemiBold",
    },
    cardTitle: {
        color: "#FFF",
        marginLeft: "5%",
        fontSize: 26,
        lineHeight: 24,
        fontFamily: "Work-Sans-SemiBold",
    },
    cardDescription: {
        flexDirection: "row",
        marginLeft: "5%",
    },
    description: {
        color: "#FFF",
        fontSize: 14,
        fontFamily: "Work-Sans-SemiBold",
    },
    song: {
        flexDirection: "row",
        alignItems: "center",
    },
    ticket: {
        marginLeft: "2%",
        flexDirection: "row",
        alignItems: "center",
    },
    descriptionIcon: {
        width: 10,
        height: 10,
        marginRight: 5,
    },
    exit: {
        alignItems: "flex-end",
        marginTop: "1%",
        marginRight: "1%",
    },
    exitIcon: {
        width: 30,
        height: 30,
        alignItems: "center",
        justifyContent: "center",
        backgroundColor: "rgba(152,152,152, 0.4)",
        shadowOpacity: 0.4,
        borderRadius: 45,
    },
    exitImage: {
        height: 8.9,
        width: 8.9,
    },
});

const collections = StyleSheet.create({
    index: {
        marginTop: "8%",
        flexDirection: "column",
    },
    header: {
        marginHorizontal: "5%",
        flexDirection: "row",
        alignItems: "center",
        justifyContent: "space-between",
    },
    title: {
        lineHeight: 36,
        fontSize: 32,
        fontFamily: "Work-Sans-Bold",
        color: "#373A42",
    },
    card: {
        marginTop: 29,
        height: "12%",
    },
    cardImage: {
        position: "absolute",
        width: "100%",
        height: "200%",
        borderRadius: 16,
    },
    cardTitle: {
        color: "#FFF",
        marginTop: "5%",
        marginLeft: "5%",
        fontSize: 26,
        lineHeight: 24,
        fontFamily: "Work-Sans-SemiBold",
    },
    description: {
        marginLeft: "5%",
        flexDirection: "row",
        alignItems: "center",
    },
    descriptionIcon: {
        marginRight: "1%",
        width: 10,
        height: 10,
        tintColor: "#BDC0C4",
    },
    descriptionText: {
        color: "#BDC0C4",
        fontSize: 14,
        fontFamily: "Work-Sans-SemiBold",
    },
    more: {
        marginTop: "8%",
        marginLeft: "5%",
        flexDirection: "row",
        alignItems: "center",
    },
    moreText: {
        color: "#FFF",
        fontSize: 18,
        fontFamily: "Work-Sans-SemiBold",
    },
    moreIcon: {
        marginTop: "0.5%",
        marginLeft: 5,
        width: 6,
        height: 6,
    },
});

const discover = StyleSheet.create({
    index: {
        flexDirection: "column",
    },
    header: {
        marginHorizontal: "5%",
        flexDirection: "row",
        alignItems: "center",
        justifyContent: "space-between",
    },
    title: {
        lineHeight: 36,
        fontSize: 32,
        fontFamily: "Work-Sans-Bold",
        color: "#373A42",
    },
    card: {
        width: "85%",
        height: 56,
        marginTop: 20,
        backgroundColor: "#FFF",
        flexDirection: "row",
        alignItems: "center",
        marginHorizontal: 25,
        borderRadius: 90,
    },
    icon: {
        width: 40,
        height: 40,
        justifyContent: "center",
        alignItems: "center",
        borderRadius: 90,
        marginLeft: 10,
    },
    iconImage: {
        width: 30,
        height: 30,
    },
    text: {
        marginLeft: 10,
        fontSize: 14,
        fontFamily: "Work-Sans-SemiBold",
    },
});

const coming = StyleSheet.create({
    index: {
        marginTop: "8%",
        flexDirection: "column",
    },
    header: {
        marginHorizontal: "5%",
        flexDirection: "column",
    },
    location: {
        flexDirection: "row",
        alignItems: "center",
    },
    locationIcon: {
        width: 9,
        height: 9,
    },
    locationText: {
        marginLeft: 10,
        color: "#CACDD4",
        fontFamily: "Work-Sans-Bold",
        fontSize: 12,
    },
    title: {
        flexDirection: "row",
        alignItems: "center",
        justifyContent: "space-between",
    },
    titleText: {
        lineHeight: 36,
        fontSize: 32,
        fontFamily: "Work-Sans-Bold",
        color: "#373A42",
    },
    titleIcon: {
        backgroundColor: "#FFF",
        width: 32,
        height: 32,
        display: "flex",
        justifyContent: "center",
        alignItems: "center",
        borderRadius: 90,
    },
    iconImage: {
        width: 21,
        height: 21,
    },
    eventMonth: {
        flexDirection: "column",
        marginTop: "5%",
    },
    eventMonthText: {
        marginLeft: "10%",
        fontFamily: "Work-Sans-Bold",
        fontSize: 14,
        color: "#FC1055",
        textTransform: "uppercase",
        marginBottom: "2%",
    },
    event: {
        flexDirection: "row",
        marginBottom: 30,
    },
    day: {
        flexDirection: "column",
        alignItems: "center",
        width: "10%",
        height: WIDTH * 0.15,
        backgroundColor: "#FFF",
        borderRadius: 12,
        marginLeft: "7.5%",
    },
    date: {
        justifyContent: "center",
    },
    dateDay: {
        fontSize: 20,
        fontFamily: "Work-Sans-SemiBold",
        marginTop: "30%",
        textAlign: "center",
    },
    dateWeek: {
        fontSize: 10,
        fontFamily: "Work-Sans-Bold",
        color: "#C1C1C1",
        textTransform: "uppercase",
    },
    eventMainCard: {
        width: "100%",
        height: 200,
        marginLeft: "10%",
        marginRight: "5%",
    },
    eventMainImage: {
        position: "absolute",
        width: "100%",
        height: "100%",
        borderRadius: 16,
    },
    eventTitle: {
        color: "#FFF",
        marginTop: 120,
        marginLeft: "6%",
        fontSize: 20,
        fontFamily: "Work-Sans-SemiBold",
    },
    eventDescription: {
        flexDirection: "row",
        marginLeft: "6%",
        alignItems: "center",
    },
    descriptionIcon: {
        width: 10,
        height: 10,
    },
    descriptionType: {
        color: "#FFF",
        marginLeft: "1%",
        fontSize: 12,
        fontFamily: "Work-Sans-SemiBold",
        marginRight: 10,
    },
    descriptionPrice: {
        color: "#FFF",
        marginLeft: "1%",
        fontSize: 12,
        fontFamily: "Work-Sans-SemiBold",
    },
    eventSubCard: {
        marginTop: "3%",
        marginLeft: "10%",
        width: "100%",
        height: 40,
    },
    eventSubImage: {
        position: "absolute",
        width: "100%",
        height: "100%",
        borderRadius: 10,
    },
    eventMore: {
        flexDirection: "row",
        justifyContent: "space-between",
        alignItems: "center",
        marginTop: 10,
        marginHorizontal: 15,
    },
    eventMoreText: {
        color: "#FFF",
        fontSize: 15,
        fontFamily: "Nunito-ExtraBold",
        textTransform: "uppercase",
    },
    eventMoreIcon: {
        width: 10,
        height: 10,
    },
});
